#pragma once

#include "Entity.h"
#include "Star.h"

class StarEntity : public Entity
{
public:
	StarEntity(float outerRadius, float innerRatio, int nFlares, const Vec2& pos, Color c)
		:
		Entity(Star::Make(outerRadius, outerRadius * innerRatio, nFlares), pos, c),
		radius(outerRadius)
	{}
	float GetRadius() const
	{
		return radius;
	}
private:
	float radius;
};