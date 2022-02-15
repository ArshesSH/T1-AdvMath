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

	void Translate( const Vec2& translation_in)
	{
		translation += translation_in;
		transform.Translation( translation_in.x, translation_in.y );
	}
	void Scale( float scale_in )
	{
		scale_x *= scale_in;
		scale_y *= scale_in;
		translation *= scale_in;
	}
	void ScaleIndependent( float scale_in_x, float scale_in_y )
	{
		scale_x *= scale_in_x;
		scale_y *= scale_in_y;
		translation.x *= scale_in_x;
		translation.y *= scale_in_y;
	}
	void Rotate( float angle_in )
	{
		angle += angle_in;
		translation.Rotate( angle_in );
	}
	void Render( Graphics& gfx )
	{
		gfx.DrawClosedPolyline( *model, translation, scale_x, scale_y, angle, c );
	}
private:
	const std::vector<Vec2>* model;
	Color c;
	Mat3 transform = Mat3::Identity();
};