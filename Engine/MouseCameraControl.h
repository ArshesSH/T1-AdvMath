#pragma once

#include "Mouse.h"
#include "Camera.h"
#include "ChiliMath.h"
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
				leftEngaged = true;
				lastPos = (Vec2)mouse.GetPos();
				break;
			case Mouse::Event::Type::LRelease:
				leftEngaged = false;
				break;
			case Mouse::Event::Type::RPress:
				rightEngaged = true;
				lastPos = (Vec2)mouse.GetPos();
				lastAngle = cam.GetAngle();
				break;
			case Mouse::Event::Type::RRelease:
				rightEngaged = false;
				break;
			}
			
			if ( leftEngaged )
			{
				const auto curPos = (Vec2)mouse.GetPos();
				// Get Delta and apply zoom distance
				auto delta = (curPos - lastPos) / cam.GetScale();
				delta.x = -delta.x;
				delta.Rotate(-cam.GetAngle());
				cam.MoveBy( delta );
				lastPos = curPos;
			}

			if ( rightEngaged )
			{
				const auto curPos = (Vec2)mouse.GetPos();
				const float delta = (curPos - lastPos).x * rotateFactor;
				cam.RotateBy( -delta );
				lastPos = curPos;
			}
		}
	}
private:
	static constexpr float zoomFactor = 1.05f;
	static constexpr float rotateFactor = 0.005f * PI;
	Camera& cam;
	Mouse& mouse;
	Vec2 lastPos;
	float lastAngle;
	bool leftEngaged = false;
	bool rightEngaged = false;
};