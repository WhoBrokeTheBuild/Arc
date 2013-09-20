#pragma once

#ifndef __ARC_SHAPES_H__
#define __ARC_SHAPES_H__

#include <string>

using std::string;

enum Shapes
{
	INVALID_SHAPE = -1,

	SHAPE_TRIANGLE,
	SHAPE_RECTANGLE,
	SHAPE_PENTAGON,
	SHAPE_HEXAGON,
	SHAPE_CIRCLE,

	NUM_SHAPES
};

const string SHAPE_NAMES[NUM_SHAPES] = 
{
	"Triangle",
	"Rectangle",
	"Pentagon",
	"Hexagon",
	"Circle"
};

#endif // __ARC_SHAPES_H__