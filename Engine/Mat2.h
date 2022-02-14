#pragma once

#include "Vec2.h"

template<typename T>
class _Mat2
{
public:
	_Vec2<T> operator*( const _Vec2<T>& v ) const
	{
		_Vec2<T> vout;
		vout.x = cells[0][0] * v.x + cells[0][1] * v.y;
		vout.y = cells[1][0] * v.x + cells[1][1] * v.y;
		return vout;
	}
	_Mat2 operator*( const _Mat2& rhs ) const
	{
		_Mat2 out;
		for ( int row = 0; row < 2; row++ )
		{
			for ( int col = 0; col < 2; col++ )
			{
				out.cells[row][col] = (T)0;
				for ( int i = 0; i < 2; i++ )
				{
					out.cells[row][col] += cells[row][i] * rhs.cells[i][col];
				}
			}
		}
		return out;
	}
	_Mat2& operator*=( const _Mat2& rhs ) const
	{
		return *this = *this * rhs;
	}
	static _Mat2 Scale( T factor )
	{
		return {
			factor,	(T)0,
			(T)0,		factor
		};
	}
	static _Mat2 Identity()
	{
		return Scale( (T)1 );
	}
	static _Mat2 FlipY()
	{
		return {
			(T)1,	(T)0,
			(T)0,	(T)-1
		}
	}
	static _Mat2 Rotation( T theta )
	{
		const auto cosT = std::cos( theta );
		const auto sinT = std::sin( theta );
		return{
			cosT,	-sinT,
			sinT,	cosT
		}
	}
public:
	// [row][col]
	T cells[2][2];
};

using Mat2 = _Mat2<float>;
using Mad2 = _Mat2<double>;