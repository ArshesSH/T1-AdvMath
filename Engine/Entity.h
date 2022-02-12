#pragma once

#include <vector>
#include "Vec2.h"
#include "Drawble.h"
#include "Colors.h"

class Entity
{
public:
	Entity( std::vector<Vec2> model, const Vec2 pos = {0.0f, 0.0f}, Color c = Colors::Yellow)
		:
		model(std::move(model)),
		pos(pos),
		c(c)
	{}
	const Vec2& GetPos() const
	{
		return pos;
	}
	void SetPos( const Vec2& pos_in )
	{
		pos = pos_in;
	}
	float GetScale() const
	{
		return scale;
	}
	void SetScale( float scale_in )
	{
		scale = scale_in;
	}
	float GetAngle() const
	{
		return angle;
	}
	void SetAngle( float angle_in )
	{
		angle = angle_in;
	}
	void SetColor( Color c_in )
	{
		c = c_in;
	}
	void TranslateBy( const Vec2& offset )
	{
		pos += offset;
	}
	Drawble GetDrawble() const
	{
		Drawble d( model, c );
		d.Rotate( angle );
		d.Scale( scale );
		d.Translate( pos );
		return d;
	}
protected:
	void SetModel( std::vector<Vec2> model_in )
	{
		model = std::move( model_in );
	}
private:
	std::vector<Vec2> model;
	Vec2 pos = {0.0f, 0.0f};
	Color c;
	float scale = 1.0f;
	float angle = 0.0f;
};