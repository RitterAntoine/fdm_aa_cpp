import time
import numpy as np
import os
from typing import NamedTuple
from enum import IntEnum

import jax
import jax.numpy as jnp
from jax import ShapeDtypeStruct, jit, lax, vmap, tree_util
from jax.lib import xla_client

x64 = os.environ.get('JAX_ENABLE_X64')
if x64 == '1' or x64 == 'True' or x64 == 'true':
    x64 = True
else:
    x64 = False

float_ = jnp.float32
int_ = jnp.int32
uint = jnp.uint32
complex_ = jnp.complex64

float_np = np.float32
int_np = np.int32
uint_np = np.uint32
complex_np = np.complex64

NAI = uint(jnp.iinfo(uint).max)

INT_MAX = int_(jnp.iinfo(int_).max)

if x64:
    float_ = jnp.float64
    int_ = jnp.int64
    uint = jnp.uint64
    complex_ = jnp.complex128

    float_np = np.float64
    int_np = np.int64
    uint_np = np.uint64
    complex_np = np.complex128


class Grid(NamedTuple): # grid/grid.py DONE
    cell_ndcount: tuple[int, ...] | np.ndarray | jnp.ndarray
    origin: tuple[int, ...] | np.ndarray | jnp.ndarray
    cell_sides_length: float | np.ndarray | jnp.ndarray

class PointData(NamedTuple): # point_data.py DONE
    point: jnp.ndarray
    data: jnp.ndarray

def count2_per_axis( # grid/edge.py DONE
    grid_cell_2dcount: jnp.ndarray) -> jnp.ndarray:
    edge_2dcount = jnp.array([[grid_cell_2dcount[0],
                               grid_cell_2dcount[1] + 1],
                              [grid_cell_2dcount[0] + 1,
                               grid_cell_2dcount[1]]])
    return edge_2dcount

def ndindex_from_1dindex( # grid/cell.py DONE
        cell_1dindex: int | uint,
        cell_ndcount: jnp.ndarray) -> jnp.ndarray:

    n = cell_ndcount.shape[0]
    cell_ndindex = jnp.zeros((n,), uint)
    cell_ndindex = cell_ndindex.at[0].set(
        uint(
            cell_1dindex %
            cell_ndcount[0]))
    for i in range(1, n):
        shift = uint(jnp.prod(cell_ndcount[:i]))
        cell_ndindex = cell_ndindex.at[i].set(
            uint(
                (cell_1dindex // shift) %
                cell_ndcount[i]))
    return cell_ndindex

def indices2_from_grid( # grid/edge.py DONE
        grid_cell_2dcount: jnp.ndarray) -> tuple[jnp.ndarray, jnp.ndarray]:
    with jax.ensure_compile_time_eval():
        edge_ndcount_per_axis = count2_per_axis(grid_cell_2dcount)
        edge_flattened_count_per_axis = jnp.array(
            [edge_ndcount_per_axis[0][0] * edge_ndcount_per_axis[0][1],
             edge_ndcount_per_axis[1][0] * edge_ndcount_per_axis[1][1]])
        edge_flattened_indices_per_axis = (
            jnp.arange(edge_flattened_count_per_axis[0]),
            jnp.arange(edge_flattened_count_per_axis[1])
        )
    edge_flattened_to_ndindex_v = vmap(
        ndindex_from_1dindex, (0, None))
    edge_ndindices_per_axis = (
        edge_flattened_to_ndindex_v(
            edge_flattened_indices_per_axis[0],
            edge_ndcount_per_axis[0]),
        edge_flattened_to_ndindex_v(
            edge_flattened_indices_per_axis[1],
            edge_ndcount_per_axis[1])
    )
    return edge_ndindices_per_axis

def endpoints( # grid/edge.py DONE
        edge_ndindex: jnp.ndarray,
        edge_axis: int,
        grid: Grid) -> jnp.ndarray:
    n = grid.cell_ndcount.shape[0]
    increment = jnp.zeros((n,), int_).at[edge_axis].set(
        1) * grid.cell_sides_length
    v0 = edge_ndindex * grid.cell_sides_length + grid.origin
    v1 = v0 + increment
    return jnp.array([v0, v1])

def index1_from_ndindex( # grid/cell.py DONE
        cell_ndindex: jnp.ndarray,
        cell_ndcount: jnp.ndarray) -> int:
    n = cell_ndcount.shape[0]
    flattened_index = cell_ndindex[0]
    for i in range(1, n):
        shift = uint(jnp.prod(jnp.array(cell_ndcount[:i])))
        flattened_index += cell_ndindex[i] * shift
    return flattened_index

def grid_edge_point_scalars( # scalar.py DONE
        edge_ndindex: jnp.ndarray,
        edge_axis: int,
        grid_scalars_flattened: jnp.ndarray,
        grid_cell_ndcount: jnp.ndarray) -> jnp.ndarray:
    shift = jnp.zeros_like(edge_ndindex).at[edge_axis].set(1)
    edge_vertex_ndindices = jnp.array([edge_ndindex, edge_ndindex + shift])
    edge_vertex_flattened_indices = vmap(
        index1_from_ndindex, (0, None))(
        edge_vertex_ndindices, grid_cell_ndcount)
    edge_scalars = grid_scalars_flattened[edge_vertex_flattened_indices]
    return edge_scalars

def float_same_sign(a: float_, b: float_) -> bool: # math.py DONE
    a_is_neg = jnp.signbit(a)
    b_is_neg = jnp.signbit(b)
    a_is_pos = jnp.logical_not(a_is_neg)
    b_is_pos = jnp.logical_not(b_is_neg)
    both_neg = jnp.logical_and(a_is_neg, b_is_neg)
    both_pos = jnp.logical_and(a_is_pos, b_is_pos)
    return jnp.logical_or(both_neg, both_pos)

def solve_linear_interpolation_equation(v1: float, v2: float) -> float: # math.py DONE
    deno = (v2 - v1)
    return jnp.where(jnp.abs(deno) < 0.0001, 0.5, -v1 / deno)

def clamp(val: float | jnp.ndarray, # math.py DONE
          low: float | jnp.ndarray,
          high: float | jnp.ndarray) -> float | jnp.ndarray:

    val = jnp.where(jnp.less(val, low), low, val)
    val = jnp.where(jnp.greater(val, high), high, val)
    return val

def grid_edge_root_point( # scalar.py DONE
        edge_ndindex: jnp.ndarray,
        edge_axis: int,
        flattened_scalar_field: jnp.ndarray,
        grid: Grid) -> jnp.ndarray:
    edge_endpoints_val = endpoints(edge_ndindex, edge_axis, grid)
    edge_point_scalars_val = grid_edge_point_scalars(
        edge_ndindex,
        edge_axis,
        flattened_scalar_field,
        grid.cell_ndcount)
    mask = float_same_sign(
        edge_point_scalars_val[0], edge_point_scalars_val[1])
    u = solve_linear_interpolation_equation(
        edge_point_scalars_val[0], edge_point_scalars_val[1])
    epsilon = 0.01
    u = clamp(u, epsilon, 1. - epsilon)
    root_point = (1. - u) * edge_endpoints_val[0] + u * edge_endpoints_val[1]
    return jnp.where(mask, jnp.full_like(root_point, jnp.nan), root_point)

def index1_from_2dindex( # grid/edge.py DONE
        edge_2dindex: jnp.ndarray,
        edge_axis: int,
        edge_2dcount: jnp.ndarray) -> uint:
    edge_flattened_index = index1_from_ndindex(
        edge_2dindex, edge_2dcount[edge_axis])
    hedge_flattened_cell_count = edge_2dcount[0][0] * edge_2dcount[0][1]
    edge_flattened_index += edge_axis * hedge_flattened_cell_count
    return uint(edge_flattened_index)

class MaskedArray(NamedTuple): # array.py DONE
    array: jnp.ndarray
    mask: jnp.ndarray

class Neighboring2Type(IntEnum): # grid/edge.py DONE
    VISIBLE = 0
    WITHIN_CELL_SIDE_LENDTH = 1

def neighboring_2dindices_direct( # grid/edge.py DONE
        edge_2dindex: jnp.ndarray,
        edge_axis: int,
        grid_cell_2dcount: jnp.ndarray,
        neighboring_type: Neighboring2Type) -> MaskedArray:

    def _get_edge_2dindex_shifts_visible_case():
        return jnp.array([[[0, -1],
                           [0, 1],
                           [INT_MAX, INT_MAX],
                           [INT_MAX, INT_MAX]],
                          [[0, -1],
                           [1, -1],
                           [0, 0],
                           [1, 0]]])

    def _get_edge_2dindex_shifts_p_repulsion_case():
        return jnp.array([[[-1, 0],
                           [1, 0],
                           [INT_MAX, INT_MAX],
                           [INT_MAX, INT_MAX]],
                          [[0, -1],
                           [1, -1],
                           [0, 0],
                           [1, 0]]])
    edge_2dcount = jnp.array(count2_per_axis(grid_cell_2dcount))
    edge_ndindex_shifts = lax.switch(
        neighboring_type,
        [_get_edge_2dindex_shifts_visible_case,
         _get_edge_2dindex_shifts_p_repulsion_case])
    edge_ndindex_shifts = lax.cond(
        edge_axis == 1,
        lambda x: jnp.flip(jnp.flip(x, axis=0), axis=2),
        lambda x: x,
        edge_ndindex_shifts)
    neighbors_ndindices = edge_2dindex.reshape((1, 1, 2)) + edge_ndindex_shifts
    neighbors_mask = jnp.logical_or(
        neighbors_ndindices >= edge_2dcount.reshape(
            (edge_2dcount.shape[0], 1, edge_2dcount.shape[1])),
        neighbors_ndindices < 0)
    neighbors_ndindices = jnp.where(neighbors_mask, 0, neighbors_ndindices)
    neighbors_mask = jnp.any(neighbors_mask, axis=2)
    return MaskedArray(neighbors_ndindices, neighbors_mask)

def grid_edge_root_existence( # scalar.py DONE
        edge_ndindex: jnp.ndarray,
        edge_axis: int,
        flattened_scalar_field: jnp.ndarray,
        grid: Grid) -> bool:

    edge_point_scalars_val = grid_edge_point_scalars(
        edge_ndindex,
        edge_axis,
        flattened_scalar_field,
        grid.cell_ndcount)

    solution_exists = jnp.logical_not(
        float_same_sign(edge_point_scalars_val[0], edge_point_scalars_val[1]))
    return solution_exists

def ndindex_is_valid( # grid/cell.py DONE
        grid_cell_ndindex: jnp.ndarray,
        grid_cell_ndcount: jnp.ndarray) -> bool:
    valid_cell_ndindex = jnp.logical_and(
        grid_cell_ndindex >= 0, grid_cell_ndindex < grid_cell_ndcount)
    return jnp.all(valid_cell_ndindex)

def corner_vertex_ndindices( # grid/cell.py DONE
        cell_ndindex: jnp.ndarray) -> jnp.ndarray:
    n = cell_ndindex.shape[0]
    corner_count = 2**n
    corner_cell_ndcount = jnp.full((n,), 2)
    corner_flattened_indices = jnp.arange(corner_count)
    corner_ndindices = vmap(
        ndindex_from_1dindex, (0, None))(
        corner_flattened_indices, corner_cell_ndcount)
    return corner_ndindices + cell_ndindex

def concatenate(pytrees: tuple) -> tuple: # tree_util.py DONE
    tree_count = len(pytrees)
    treedef = tree_util.tree_structure(pytrees[0])
    leaf_list = []
    for i_tree in range(tree_count):
        leaves_i_tree = tree_util.tree_leaves(pytrees[i_tree])
        leaf_list.append(leaves_i_tree)
    leaf_count = len(leaf_list[0])

    leaves_concatenated = []
    for i_leaf in range(leaf_count):
        leaf_i_all_trees = []
        for i_tree in range(tree_count):
            leaf_i_all_trees.append(leaf_list[i_tree][i_leaf])
        leaves_concatenated.append(jnp.concatenate(leaf_i_all_trees))
    return treedef.unflatten(leaves_concatenated)

def grid2_contour( # scalar.py
        scalar_field_flattened: jnp.ndarray,
        scalar_field_cell_2dcount: tuple[int, int],
        scalar_field_grid: Grid) -> PointData:

    def uniform_grid_edge_root_point_and_adjacency(
            edge_ndindex: jnp.ndarray,
            edge_axis: int,
            scalar_1darray: jnp.ndarray,
            scalar_grid_param: Grid) -> PointData:

        class GetEdgeAdjacencyParams(NamedTuple):
            """
            This class groups the parameters of the get_edge_adjacency
            functions.
            """
            edge_ndindex: jnp.ndarray
            edge_axis: int
            edge_side: int
            edge_cell_ndcount: jnp.ndarray
            same_side_corner_and_center: bool

        def _get_edge_adjacency_no_extraction_case(
                params: GetEdgeAdjacencyParams) -> uint:
            return NAI

        def _convert_edge_shift_to_adjacency(
                shift: jnp.ndarray,
                params: GetEdgeAdjacencyParams,
                adjacent_edge_axis: int) -> uint:
            shift = lax.cond(params.edge_axis == 1,
                             lambda x: x[::-1], lambda x: x, shift)
            adjacent_edge_ndindex = params.edge_ndindex + shift
            temp = params.edge_cell_ndcount
            return index1_from_2dindex(
                adjacent_edge_ndindex,
                adjacent_edge_axis,
                params.edge_cell_ndcount)

        def _get_edge_adjacency_case_001(
                params: GetEdgeAdjacencyParams) -> uint:
            shift = jnp.array([1, -1 + params.edge_side])
            adjacent_edge_axis = (params.edge_axis + 1) % 2
            return _convert_edge_shift_to_adjacency(
                shift,
                params,
                adjacent_edge_axis)

        def _get_edge_adjacency_case_010(
                params: GetEdgeAdjacencyParams) -> uint:
            shift = jnp.array([0, -1 + params.edge_side])
            adjacent_edge_axis = (params.edge_axis + 1) % 2
            return _convert_edge_shift_to_adjacency(
                shift,
                params,
                adjacent_edge_axis)

        def _get_edge_adjacency_case_100(
                params: GetEdgeAdjacencyParams) -> uint:
            shift = jnp.array([0, -1 + 2 * params.edge_side])
            return _convert_edge_shift_to_adjacency(
                shift,
                params,
                params.edge_axis)

        def _get_edge_adjacency_case_111(
                params: GetEdgeAdjacencyParams) -> uint:
            return lax.cond(
                params.same_side_corner_and_center,
                lambda x: _get_edge_adjacency_case_001(x),
                lambda x: _get_edge_adjacency_case_010(x),
                params)

        grid_edge_root_point_val = grid_edge_root_point(
            edge_ndindex,
            edge_axis,
            scalar_1darray,
            scalar_grid_param) + scalar_grid_param.cell_sides_length * 0.5

        hedge_ndcell_count = (
            scalar_grid_param.cell_ndcount[0] - 1,
            scalar_grid_param.cell_ndcount[1])
        vedge_ndcell_count = (
            scalar_grid_param.cell_ndcount[0],
            scalar_grid_param.cell_ndcount[1] - 1)
        edge_cell_ndcount = jnp.array((hedge_ndcell_count, vedge_ndcell_count))
        contour_grid_cell_count = (
            scalar_grid_param.cell_ndcount[0] - 1,
            scalar_grid_param.cell_ndcount[1] - 1)

        visible_neighbors_ndindices = neighboring_2dindices_direct(
            edge_ndindex,
            edge_axis,
            contour_grid_cell_count,
            Neighboring2Type.VISIBLE)

        edge_root_existence = []
        for i_axis in range(2):
            edge_root_existence.append(
                vmap(
                    grid_edge_root_existence,
                    (0,
                     None,
                     None,
                     None))(
                    visible_neighbors_ndindices.array[i_axis],
                    i_axis,
                    scalar_1darray,
                    scalar_grid_param))
        for i_axis in range(2):
            edge_root_existence[i_axis] = jnp.logical_and(
                edge_root_existence[i_axis], jnp.logical_not(
                    visible_neighbors_ndindices.mask[i_axis]))
        edge_root_existence = jnp.array(edge_root_existence)

        next_edge_axis = (edge_axis + 1) % 2
        root_exist_config = \
            jnp.array([[edge_root_existence[edge_axis][0],
                        edge_root_existence[next_edge_axis][0],
                        edge_root_existence[next_edge_axis][1]],
                       [edge_root_existence[edge_axis][1],
                        edge_root_existence[next_edge_axis][2],
                        edge_root_existence[next_edge_axis][3]]])

        cell_shift = lax.cond(edge_axis == 0, lambda x: jnp.array(
            [0, -1]), lambda x: jnp.array([-1, 0]), None)
        edge_adjacent_cells_ndindices = jnp.array(
            [edge_ndindex + cell_shift, edge_ndindex])
        edge_adjacent_cells_ndindices_mask = jnp.logical_not(
            vmap(ndindex_is_valid, (0, None))(
                edge_adjacent_cells_ndindices,
                jnp.array(contour_grid_cell_count)))
        edge_adjacent_cells_ndindices = jnp.where(
            edge_adjacent_cells_ndindices_mask.reshape(-1, 1),
            0,
            edge_adjacent_cells_ndindices)
        grid_corner_vertex_ndindices = vmap(
            corner_vertex_ndindices, (0,))(edge_adjacent_cells_ndindices)
        grid_corner_1dindices = vmap(
            index1_from_ndindex, (0, None))(
            grid_corner_vertex_ndindices.reshape(
                (-1, 2)), scalar_grid_param.cell_ndcount)
        corner_scalars = scalar_1darray[grid_corner_1dindices].reshape(2, 4)
        average_scalar = jnp.average(corner_scalars, axis=1)
        same_side_corner_and_center = []
        ref_corner_verter_value = scalar_1darray[index1_from_ndindex(
            edge_ndindex, scalar_grid_param.cell_ndcount)]
        for i_side in range(2):
            same_side_corner_and_center.append(
                average_scalar[i_side] * ref_corner_verter_value)
        same_side_corner_and_center = jnp.array(same_side_corner_and_center)
        same_side_corner_and_center = same_side_corner_and_center >= 0.
        case_index = jnp.array(
            [4 * root_exist_config[0][0] +
             2 * root_exist_config[0][1] +
             1 * root_exist_config[0][2],
             4 * root_exist_config[1][0] +
             2 * root_exist_config[1][1] +
             1 * root_exist_config[1][2]])

        branches = (
            _get_edge_adjacency_no_extraction_case,  # 000: 0
            _get_edge_adjacency_case_001,            # 001: 1
            _get_edge_adjacency_case_010,            # 010: 2
            _get_edge_adjacency_no_extraction_case,  # 011: 3
            _get_edge_adjacency_case_100,            # 100: 4
            _get_edge_adjacency_no_extraction_case,  # 101: 5
            _get_edge_adjacency_no_extraction_case,  # 110: 6
            _get_edge_adjacency_case_111,            # 111: 7
            )

        adjacency_list = []
        for i_side in range(2):
            get_edge_adjacency_params_i = GetEdgeAdjacencyParams(
                edge_ndindex,
                edge_axis,
                i_side,
                edge_cell_ndcount,
                same_side_corner_and_center[i_side])
            adjacency_list.append(
                lax.switch(
                    case_index[i_side],
                    branches,
                    get_edge_adjacency_params_i))
        adjacency_array = jnp.array(adjacency_list, float_)

        adjacency_array = jnp.where(
            jnp.equal(adjacency_array, NAI),
            jnp.nan,
            adjacency_array)

        return PointData(grid_edge_root_point_val, adjacency_array)

    with jax.ensure_compile_time_eval():
        contour_grid_edge_2dindices = indices2_from_grid(
            jnp.array(scalar_field_cell_2dcount) - 1)
    v_h: PointData = vmap(
        uniform_grid_edge_root_point_and_adjacency, (0, None, None, None))(
        contour_grid_edge_2dindices[0],
        0,
        scalar_field_flattened,
        scalar_field_grid)
    v_v: PointData = vmap(
        uniform_grid_edge_root_point_and_adjacency, (0, None, None, None))(
        contour_grid_edge_2dindices[1],
        1,
        scalar_field_flattened,
        scalar_field_grid)
    res = concatenate((v_h, v_v))
    return res

def all_isclose_masked(a: PointData, b: PointData) -> bool: # tree_util.py
    mask_a = jnp.logical_not(jnp.isnan(a.point))
    mask_b = jnp.logical_not(jnp.isnan(b.point))
    return jnp.all(jnp.isclose(a.point[mask_a], b.point[mask_b]))

def helper_grid2_contour():
    scalar_field_cell_2dcount = (2, 3)
    cell_2dcount = jnp.array(scalar_field_cell_2dcount)
    origin = jnp.array([0.0, 0.0])
    cell_sides_length = 1.
    scalar_field_param = Grid(cell_2dcount, origin, cell_sides_length)
    grid_scalars_flattened = jnp.array([-0.5, 0.5, -0.25, 0.75, -0.1, 0.9])
    contour = grid2_contour(grid_scalars_flattened, scalar_field_cell_2dcount, scalar_field_param)
    print("Contour: ", contour)
    contour_exp = PointData(
        point=jnp.array([[1., 0.5], [0.75, 1.5], [0.6, 2.5], [jnp.nan, jnp.nan], [jnp.nan, jnp.nan], [jnp.nan, jnp.nan], [jnp.nan, jnp.nan]]),
        data=jnp.array([[jnp.nan,  1.], [0.,  2.], [1., jnp.nan], [jnp.nan, jnp.nan], [jnp.nan, jnp.nan], [jnp.nan, jnp.nan], [jnp.nan, jnp.nan]]))
    print("Expected Contour: ", contour_exp)
    result = all_isclose_masked(contour, contour_exp)
    print("Comparison Result: ", result)
    return result

helper_grid2_contour()