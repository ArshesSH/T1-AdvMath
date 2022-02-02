#pragma once

#include "Mouse.h"
#include "Camera.h"
class MouseCameraControl
{
public:
	MouseCameraControl(Camera& cam, Mouse& mouse)
		:
		cam(cam),
		mouse(mouse)
	{}

	void Update()
	{
		while ( !mouse.IsEmpty() )
		{
			const auto e = mouse.Read();
			switch ( e.GetType() )
			{
			case Mouse::Event::Type::WheelUp:
				cam.SetScale( cam.GetScale() * zoomFactor );
				break;
			case Mouse::Event::Type::WheelDown:
				cam.SetScale( cam.GetScale() / zoomFactor );
				break;
			case Mouse::Event::Type::LPress:
				engaged = true;
				lastPos = (Vec2)mouse.GetPos();
				break;
			case Mouse::Event::Type::LRelease:
				engaged = false;
				break;
			}
			
			if ( engaged )
			{
				const auto curPos = (Vec2)mouse.GetPos();
				// Get Delta and apply zoom distance
				auto delta = (curPos - lastPos) / cam.GetScale();
				delta.x = -delta.x;
				cam.MoveBy( delta );
				lastPos = curPos;
			}
		}
	}
private:
	static constexpr float zoomFactor = 1.05f;
	Camera& cam;
	Mouse& mouse;
	Vec2 lastPos;
	bool engaged = false;
};