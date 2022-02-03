#pragma once

#include "Vec2.h"

template<typename T>
class _Rect
{
public:
	_Rect() = default;
	_Rect( T left_in, T right_in, T top_in, T bottom_in )
		:
		left( left_in ),
		right( right_in ),
		top( top_in ),
		bottom( bottom_in )
	{
	}

	_Rect( const _Vec2<T>& topLeft, const _Vec2<T>& bottomRight )
		:
		_Rect( topLeft.x, bottomRight.x, topLeft.y, bottomRight.y )
	{
	}

	_Rect( const _Vec2<T>& topLeft, T width, T height )
		:
		_Rect( topLeft, topLeft + _Vec2<T>( width, height ) )
	{
	}

	bool IsOverlappingWith( const _Rect& other ) const
	{
		return right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom;
	}

	bool IsContainedBy( const _Rect& other ) const
	{
		return left >= other.left && right <= other.right &&
			top >= other.top && bottom <= other.bottom;
	}

	bool Contains( const _Vec2<T>& point ) const
	{
		return point.x >= left && point.x < right&& point.y >= top && point.y < bottom;
	}

	_Rect FromCenter( const _Vec2<T>& center, T halfWidth, T halfHeight )
	{
		const _Vec2<T> half( halfWidth, halfHeight );
		return _Rect( center - half, center + half );
	}

	_Rect GetExpanded( T offset ) const
	{
		return _Rect( left - offset, right + offset, top - offset, bottom + offset );
	}

	_Vec2<T> GetCenter() const
	{
		return _Vec2<T>( (left + right) / 2, (top + bottom) / 2 );
	}

	T GetWidth() const
	{
		return right - left;
	}

	T GetHeight() const
	{
		return bottom - top;
	}
public:
	T left;
	T right;
	T top;
	T bottom;
};
typedef _Rect<float> RectF;
typedef _Rect<int> RectI;