/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "RectF.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ct(gfx),
	cam(ct),
	camControl(cam, wnd.mouse),
	plank( { 0,0 }, -380.0f, -300.0f, 300.0f, 20.0f, Colors::Yellow ),
	shooter( { 0, -300.0f } )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	if ( wnd.kbd.KeyIsPressed( VK_UP ) )
	{
		plank.MoveFreeYBy( 3 );
	}
	else if ( wnd.kbd.KeyIsPressed( VK_DOWN ) )
	{
		plank.MoveFreeYBy( -3 );
	}

	camControl.Update();
	
	// Generate balls
	time += dt;
	if ( time >= period )
	{
		time -= period;
		balls.push_back(shooter.GenerateBall());
	}

	// Update balls
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

void Game::ComposeFrame()
{
	cam.Draw( plank.GetDrawble() );
	for ( auto& b : balls )
	{
		cam.Draw( b.GetDrawble() );
	}
}
