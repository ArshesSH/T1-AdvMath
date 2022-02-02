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
#include <random>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ct(gfx),
	cam(ct),
	camControl(cam, wnd.mouse)
{
	field.MakeRandomField();
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
	constexpr float speed = 3.0f;
	if ( wnd.kbd.KeyIsPressed( VK_DOWN ) )
	{
		cam.MoveBy( { 0.0f, -speed } );
	}
	if ( wnd.kbd.KeyIsPressed( VK_UP ) )
	{
		cam.MoveBy( { 0.0f, speed } );
	}
	if ( wnd.kbd.KeyIsPressed( VK_RIGHT ) )
	{
		cam.MoveBy( { speed, 0.0f } );
	}
	if ( wnd.kbd.KeyIsPressed( VK_LEFT ) )
	{
		cam.MoveBy( { -speed, 0.0f } );
	}

	camControl.Update();

	//while ( !wnd.mouse.IsEmpty() )
	//{
	//	const auto e = wnd.mouse.Read();
	//	if ( e.GetType() == Mouse::Event::Type::WheelUp )
	//	{
	//		cam.SetScale( cam.GetScale() * 1.05f);
	//	}
	//	else if ( e.GetType() == Mouse::Event::Type::WheelDown )
	//	{
	//		cam.SetScale( cam.GetScale() * 0.95f );
	//	}
	//}

}

void Game::ComposeFrame()
{
	for ( const auto& e : field.GetField() )
	{
		cam.Draw( e->GetDrawble() );
	}
}
