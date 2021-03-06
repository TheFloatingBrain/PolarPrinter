#include "Renderer.h"
#include <math.h>
#include <utility>

#ifndef SHAPES_HEADER_H
#define SHAPES_HEADER_H
    std::vector< float > GenerateGear( unsigned int sides, float scale, float toothLength );
    std::vector< float > GenerateHollowGear( unsigned int sides, float width, float scale, float outerToothLength, float innerToothLength );
#endif
