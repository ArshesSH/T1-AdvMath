#pragma once

#include "BallEntity.h"
#include <random>

class BallShooter
{
public:
	BallShooter( Vec2 pos )
		:
		pos(pos)
	{}
	BallEntity GenerateBall()
	{
		std::mt19937 rng( std::random_device{}() );
		std::normal_distribution<float> velXDist( meanVelX, devVelX );
		std::normal_distribution<float> velYDist( meanVelY, devVelY );
		std::normal_distribution<float> radDist( meanRad, devRad );
		const Vec2 vel{ velXDist( rng ), velYDist( rng ) };
		const float rad = radDist( rng );

		return std::move( BallEntity( rad, pos, vel, Colors::Red ) );
	}
private:
	static constexpr float removeCoord = 1000.0f;
	static constexpr float meanVelY = 1.0f;
	static constexpr float devVelY = 0.5f;
	static constexpr float minVelY = 0.2f;
	static constexpr float maxVelY = 1.5f;
	static constexpr float meanVelX = -0.5f;
	static constexpr float devVelX = 0.2f;
	static constexpr float minVelX = -1.5f;
	static constexpr float maxVelX = 0.0f;
	static constexpr float meanRad = 20.0f;
	static constexpr float devRad = 5.0f;
	static constexpr float minRad = 10.0f;
	static constexpr float maxRad = 30.0f;
	Vec2 pos;
};