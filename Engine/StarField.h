#pragma once

#include "StarEntity.h"
#include <memory>
#include <vector>
#include <random>
#include <algorithm>

class StarField
{
public:
	StarField() = default;
	void MakeRandomField()
	{
		std::mt19937 rng( std::random_device{}() );
		std::uniform_real_distribution<float> xDist( -fieldWidth / 2.0f, fieldWidth / 2.0f );
		std::uniform_real_distribution<float> yDist( -fieldHeight / 2.0f, fieldHeight / 2.0f );
		std::normal_distribution<float> radiusDist( outerMean, outerDev );
		std::normal_distribution<float> ratioDist( innerRatioMean, innerRatioDev );
		std::normal_distribution<float> flareDist( flareMean, flareDev );
		const Color colors[] = { Colors::Blue, Colors::White, Colors::Cyan, Colors::Red, Colors::Yellow };
		std::uniform_int_distribution<size_t> colorSampler( 0, std::end( colors ) - std::begin( colors ) );

		while ( field.size() < nStars )
		{
			const float rad = std::clamp( radiusDist(rng), outerMin, outerMax);
			const Vec2 pos = { xDist( rng ), yDist( rng ) };

			// If new star collide with any of starfield's star 
			if ( std::any_of( field.begin(), field.end(),
				[&]( const std::unique_ptr<StarEntity>& e ) {return (e->GetRadius() + rad) >= (e->GetPos() - pos).Len(); } )
				)
			{
				continue;
			}

			const float ratio = std::clamp( ratioDist( rng ), innerRatioMin, innerRatioMax );
			const int nFlares = std::clamp( (int)flareDist( rng ), flareMin, flareMax );
			const Color c = colors[colorSampler( rng )];

			field.emplace_back( std::make_unique<StarEntity>( rad, ratio, nFlares, pos, c ) );
		}
	}

	const std::vector<std::unique_ptr<StarEntity>>& GetField() const
	{
		return field;
	}

private:
	static constexpr int fieldWidth = 10000;
	static constexpr int fieldHeight = 8000;
	static constexpr int nStars = 500;
	static constexpr float outerMax = 300.0f;
	static constexpr float outerMin = 40.0f;
	static constexpr float outerMean = 170.0f;
	static constexpr float outerDev = 90.0f;
	static constexpr float innerRatioMax = 0.8f;
	static constexpr float innerRatioMin = 0.15f;
	static constexpr float innerRatioMean = 0.4f;
	static constexpr float innerRatioDev = 0.25f;
	static constexpr int flareMax = 10;
	static constexpr int flareMin = 3;
	static constexpr float flareMean = 6.5f;
	static constexpr float flareDev = 2.0f;

	std::vector<std::unique_ptr<StarEntity>> field;
};