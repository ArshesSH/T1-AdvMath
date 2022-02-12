#pragma once

#include "Entity.h"
#include "Star.h"
#include "RectF.h"
#include <math.h>

class StarEntity : public Entity
{
public:
	StarEntity(float outerRadius, float innerRatio, int nFlares, const Vec2& pos, Color c, float colorFreq, float colorPhase, float radiusFreq, float spinFreq )
		:
		Entity(Star::Make(outerRadius, outerRadius * innerRatio, nFlares), pos, c),
		radius(outerRadius),
		baseColor(c),
		colorFreq(colorFreq),
		colorPhase(colorPhase),
		radiusFreq(radiusFreq),
		spinFreq(spinFreq)
	{}
	float GetRadius() const
	{
		return radius;
	}
	RectF GetStarRect() const
	{
		return RectF::FromCenter( GetPos(), GetRadius(), GetRadius() );
	}
	void Update( float dt )
	{
		time += dt;
		Pulse();
		SizeTransit();
		Spin();
	}
private:
	void Pulse()
	{
		const int offset = int( 127 * sin( colorFreq * time + colorPhase ) ) + 128;
		Color c;
		c.SetR( std::min( baseColor.GetR() + offset, 255 ) );
		c.SetG( std::min( baseColor.GetG() + offset, 255 ) );
		c.SetB( std::min( baseColor.GetB() + offset, 255 ) );
		SetColor( c );
	}
	void SizeTransit()
	{
		const float offset = (sin( radiusFreq * time * 3.141592f  ) + 1.0f) / 3.0f;
		SetScale( 1.0 - offset );
	}
	void Spin()
	{
		SetAngle( spinFreq * time );
	}
private:
	float radius;
	float time = 0.0f;
	Color baseColor;
	float colorFreq;
	float colorPhase;
	float radiusFreq;
	float radiusPhase;
	float spinFreq;
};