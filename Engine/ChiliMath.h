#pragma once

#include <cmath>
#include "Vec2.h"

constexpr double PI_D = 3.141592653589793238462643383279;
constexpr float PI = (float)PI_D;

template<typename T>
auto sq( T x )
{
	return x * x;
}

template<typename T>
T DistancePointLine( const _Vec2<T>& p0, const _Vec2<T>& p1, const _Vec2<T>& q )
{
	const T a = p1.y - p0.y;
	const T b = p0.x - p1.x;
	const T c = p0.x * p1.y - p1.x * p0.y;

	return std::abs( a * q.x + b * q.y + c ) / std::sqrt( sq( a ) + sq( b ) );
}