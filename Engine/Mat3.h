#pragma once

#include "Vec3.h"

template<typename T>
class _Mat3
{
public:
	_Vec2<T> operator*( const _Vec2<T>& v )const
	{
		return _Vec2<T>( *this * (_Vec3<T>)v );
	}
	_Vec3<T> operator*( const _Vec3<T>& v ) const
	{
		_Vec3<T> vout;
		vout.x = cells[0][0] * v.x + cells[0][1] * v.y + cells[0][2] * v.w;
		vout.y = cells[1][0] * v.x + cells[1][1] * v.y + cells[1][2] * v.w;
		vout.w = cells[2][0] * v.x + cells[2][1] * v.y + cells[2][2] * v.w;
		return vout;
	}
	_Mat3 operator*( const _Mat3& rhs ) const
	{
		_Mat3 out;
		for ( int row = 0; row < 3; row++ )
		{
			for ( int col = 0; col < 3; col++ )
			{
				out.cells[row][col] = (T)0;
				for ( int i = 0; i < 3; i++ )
				{
					out.cells[row][col] += cells[row][i] * rhs.cells[i][col];
				}
			}
		}
		return out;
	}
	_Mat3& operator*=( const _Mat3& rhs ) const
	{
		return *this = *this * rhs;
	}
	static _Mat3 Scale( T factor )
	{
		return {
			factor,	(T)0,	(T)0,
			(T)0,	factor,	(T)0,
			(T)0,	(T)0,	(T)1
		};
	}
	static _Mat3 Identity()
	{
		return Scale( (T)1 );
	}
	static _Mat3 FlipY()
	{
		return {
			(T)1,	(T)0,	(T)0,
			(T)0,	(T)-1,	(T)0,
			(T)0,	(T)0,	(T)1
		}
	}
	static _Mat3 Rotation( T theta )
	{
		const auto cosT = std::cos( theta );
		const auto sinT = std::sin( theta );
		return{
			cosT,	-sinT,	(T)0,
			sinT,	cosT,	(T)0,
			(T)0,	(T)0,	(T)1
		}
	}
	static _Mat3 Translation( T x, T y )
	{
		return{
			(T)1,	(T)0,	(T)x,
			(T)0,	(T)1,	(T)y,
			(T)0,	(T)0,	(T)1
		}
	}
public:
	// [row][col]
	T cells[3][3];
};

using Mat3 = _Mat3<float>;
using Mad2 = _Mat3<double>;