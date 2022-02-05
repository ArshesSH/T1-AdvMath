#pragma once

#include "BallEntity.h"
#include <vector>
#include <random>

class BallShooter
{
public:
	BallShooter( Vec2 pos )
		:
		pos(pos)
	{}

	std::vector<BallEntity> GetBalls()
	{
		return balls;
	}

	void Update( float dt )
	{
		time += dt;
		if ( time >= period )
		{
			time -= period;
			GenerateBall();
		}
		for ( auto it = balls.begin(); it != balls.end(); )
		{
			it->Update();

			const Vec2 pos = it->GetPos();
			if ( pos.x > removeCoord || pos.x < -removeCoord || pos.y > removeCoord || pos.y < -removeCoord )
			{
				it = balls.erase( it );
			}
			else
			{
				++it;
			}
		}
	}

private:
	void GenerateBall()
	{
		std::mt19937 rng( std::random_device{}() );
		std::normal_distribution<float> velXDist( meanVelX, devVelX );
		std::normal_distribution<float> velYDist( meanVelY, devVelY );
		std::normal_distribution<float> radDist( meanRad, devRad );
		const Vec2 vel{ velXDist( rng ), velYDist( rng ) };
		const float rad = radDist( rng );

		balls.push_back( BallEntity( rad, pos, vel, Colors::Red ) );
	}

private:
	static constexpr float removeCoord = 1000.0f;
	static constexpr float meanVelY = 1.0f;
	static constexpr float devVelY = 0.5f;
	static constexpr float minVelY = 0.2f;
	static constexpr float maxVelY = 1.5f;
	static constexpr float meanVelX = 0.0f;
	static constexpr float devVelX = 0.2f;
	static constexpr float minVelX = -0.5f;
	static constexpr float maxVelX = 0.5f;
	static constexpr float meanRad = 20.0f;
	static constexpr float devRad = 5.0f;
	static constexpr float minRad = 10.0f;
	static constexpr float maxRad = 30.0f;
	static constexpr float period = 1.5f;
	std::vector<BallEntity> balls;
	Vec2 pos;
	float time = 0.0f;
};