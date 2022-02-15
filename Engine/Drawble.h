#pragma once

#include "Graphics.h"
#include <vector>
#include "Vec2.h"
#include "Mat3.h"
#include "Colors.h"

class Drawble
{
public:
	Drawble( const std::vector<Vec2>& model, Color c )
		:
		model(&model),
		c(c)
	{}

	void ApplyTransformation( const Mat3& transformation_in )
	{
		transform = transformation_in * transform;
	}
	void Render( Graphics& gfx )
	{
		gfx.DrawClosedPolyline( *model, transform, c );
	}
private:
	const std::vector<Vec2>* model;
	Color c;
	Mat3 transform = Mat3::Identity();
};