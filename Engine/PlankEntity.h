#pragma once

#include "Entity.h"
#include "Vec2.h"
#include <vector>
#include <algorithm>

class PlankEntity : public Entity
{
public:
	PlankEntity( Vec2 fixedPoint, float freeX, float minFreeY, float maxFreeY, float thick, Color c )
		:
		Entity( {}, fixedPoint, c ),
		minFreeYModel(minFreeY - fixedPoint.y),
		maxFreeYModel(maxFreeY - fixedPoint.y),
		freeMovePos(freeX - fixedPoint.x, minFreeYModel),
		thickness(thick)
	{}
	Vec2 GetFreePos() const
	{
		return freeMovePos + GetPos();
	}
	Vec2 GetSurfaceVec() const
	{
		return -freeMovePos;
	}
	auto GetPoint()
	{
		const Vec2 pos = GetPos();
		return std::make_pair( pos, pos + freeMovePos );
	}
	float GetFreeY() const
	{
		return freeMovePos.y;
	}
	void SetFreeY( float y )
	{
		freeMovePos.y = std::clamp( y, minFreeYModel, maxFreeYModel );
	}
	void MoveFreeYBy( float delta )
	{
		SetFreeY( GetFreeY() + delta );
	}
	Drawble GetDrawble()
	{
		std::vector<Vec2> model;
		model.reserve( 4 );
		model.emplace_back( 0.0f, 0.0f );
		model.push_back( freeMovePos );
		model.push_back( freeMovePos + Vec2{ 0.0f, thickness } );
		model.emplace_back( 0.0f, thickness );
		SetModel( std::move( model ) );
		return Entity::GetDrawble();
	}
private:
	float minFreeYModel;
	float maxFreeYModel;
	Vec2 freeMovePos;
	float thickness;
};