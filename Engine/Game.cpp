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

	shooter.Update( dt );

	if ( wnd.kbd.KeyIsPressed( VK_UP ) )
	{
		plank.MoveFreeYBy( 3 );
	}
	else if ( wnd.kbd.KeyIsPressed( VK_DOWN ) )
	{
		plank.MoveFreeYBy( -3 );
	}

	camControl.Update();
}

void Game::ComposeFrame()
{
	cam.Draw( plank.GetDrawble() );
	for ( auto& b : shooter.GetBalls() )
	{
		cam.Draw( b.GetDrawble() );
	}
}
