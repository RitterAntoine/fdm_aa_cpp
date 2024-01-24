#pragma once

#include <LibSL/Math/Vertex.h>
#include "grid.h"

std::pair<LibSL::Math::v2f, LibSL::Math::v2f> endpoints(LibSL::Math::v2i edgeIndex, int edgeAxis, const Grid& grid);