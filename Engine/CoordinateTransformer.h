#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include "Drawble.h"
#include <vector>

class CoordinateTransformer
{
public:
	CoordinateTransformer( Graphics& gfx )
		:
		gfx(gfx)
	{}

	void Draw( Drawble& drawble ) const 
	{
		Vec2 originPos = { (float)gfx.ScreenWidth / 2.0f, (float)gfx.ScreenHeight / 2.0f };
		drawble.ScaleIndependent( 1.0f, -1.0f );
		drawble.Translate( originPos );
		drawble.Render( gfx );
	}

private:
	Graphics& gfx;
};