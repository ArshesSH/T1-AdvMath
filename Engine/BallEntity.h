#pragma once

#include "Entity.h"
#include "Star.h"

class BallEntity : public Entity
{
public:
	BallEntity(float radius, Vec2 startPos, Vec2 velocity, Color c)
		:
		Entity(Star::Make(radius, radius, 8), startPos, c),
		radius(radius),
		vel(velocity)
	{}

	float GetRadius() const
	{
		return radius;
	}
	Vec2 GetVel() const
	{
		return vel;
	}
	void SetVel( Vec2 vel_in )
	{
		vel = vel_in;
	}
	void Update( float dt )
	{
		time += dt;
		Transit();
	}
private:
	void Transit()
	{
		const Vec2 pos = GetPos() + (vel * time);
		SetPos( pos );
	}

private:
	float radius;
	Vec2 vel = {0, 0};
	float time = 0.0f;
};