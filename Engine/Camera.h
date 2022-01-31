#pragma once

#include "CoordinateTransformer.h"
#include "Drawble.h"

class Camera
{
public:
	Camera( CoordinateTransformer& ct, const Vec2& pos = {0.0f, 0.0f}, float scale = 1.0f)
		:
		ct(ct),
		pos(pos),
		scale( scale )
	{}

	const Vec2& GetPos() const
	{
		return pos;
	}
	void SetPos( const Vec2& pos_in)
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
	void MoveBy( const Vec2& offset )
	{
		pos += offset;
	}
	void ScaledBy( float scale_in )
	{
		scale *= scale_in;
	}
	void Draw( Drawble& drawble )
	{
		drawble.Translate( -pos );
		drawble.Scale( scale );
		ct.Draw( std::move(drawble) );
	}

private:
	CoordinateTransformer& ct;
	Vec2 pos = { 0.0f, 0.0f };
	float scale = 1.0f;
};