#pragma once

#include "CoordinateTransformer.h"
#include "Drawble.h"
#include "Graphics.h"
#include "RectF.h"

class Camera
{
public:
	Camera( CoordinateTransformer& ct, const Vec2& pos = {0.0f, 0.0f}, float scale = 1.0f, float angle = 0.0f)
		:
		ct(ct),
		pos(pos),
		scale( scale ),
		angle( angle )
	{}

	const Vec2& GetPos() const
	{
		return pos;
	}
	void SetPos( const Vec2& pos_in)
	{
		pos = pos_in;
	}
	float GetAngle() const
	{
		return angle;
	}
	void SetAngle( float angle_in )
	{
		angle = angle_in;
	}
	float GetScale() const
	{
		return scale;
	}
	void SetScale( float scale_in )
	{
		scale = scale_in;
	}
	void RotateBy( float angle_in )
	{
		angle += angle_in;
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
		drawble.Rotate( angle );
		ct.Draw( std::move(drawble) );
	}
	const RectF& GetScreenRect()
	{
		const float halfWidth = float( Graphics::ScreenWidth / 2 );
		const float halfHeight = float( Graphics::ScreenHeight / 2 );
		return RectF::FromCenter( pos, halfWidth / scale, halfHeight / scale );
	}

private:
	CoordinateTransformer& ct;
	Vec2 pos = { 0.0f, 0.0f };
	float scale = 1.0f;
	float angle = 0.0f;
};