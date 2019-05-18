#pragma once
#include"header.h"

class Vector2
{
public:
	float x;
	float y;

public:
	Vector2( ) : x( 0.0f ), y( 0.0f ) { };
	~Vector2( ) { };
	Vector2( float x, float y ) : x(x), y(y) { };

	inline float Length( ) const
	{
		return ::sqrt( x * x + y * y );
	}

	inline Vector2& Normorlize( )
	{
		float length = Length( );
		assert( length > 0 );
		x /= length; y /= length;
		return *this;
	}


	inline float Dot( const Vector2& v )
	{
		return x * v.x + y * v.y;
	}

	Vector2 operator + ( const Vector2& v ) const
	{
		return Vector2( x + v.x, y + v.y );
	}

	Vector2 operator - ( const Vector2& v ) const
	{
		return Vector2( x - v.x, y - v.y );
	}

	Vector2 operator * ( const Vector2& v ) const
	{
		return Vector2( x * v.x, y * v.y );
	}
};

class Vector3
{
public:
	float x;
	float y;
	float z;

public:
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {};
	~Vector3() { };
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

	inline float Length() const
	{
		return	::sqrt(x * x + y * y + z * z);
	}

	inline Vector3& Normorlize()
	{
		float length = Length();
		assert(length > 0);
		x /= length; y /= length; z /= length;
		return *this;
	}

	inline float Dot( const Vector3& v )
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline Vector3 Cross(const Vector3& v) const
	{
		return Vector3(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}

	Vector3 operator + (const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator - (const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator * (const Vector3& v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}
};

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

public:
	Vector4( ) : x( 0.0f ), y( 0.0f ), z( 0.0f ), w(0.0f) { };
	~Vector4( ) { };
	Vector4( float x, float y, float z, float w ) : x( x ), y( y ), z( z ), w ( w ) { };

	inline float Length( ) const
	{
		return	(float)::sqrt( x * x + y * y + z * z + w * w );
	}

	inline Vector4& Normorlize()
	{
		float length = Length();
		assert(length > 0);
		x /= length; y /= length; z /= length; w /= length;
		return *this;
	}

	Vector4 operator + ( const Vector4& v ) const
	{
		return Vector4( x + v.x, y + v.y, z + v.z, w + v.w );
	}

	Vector4 operator - ( const Vector4& v ) const
	{
		return Vector4( x - v.x, y - v.y, z - v.z, w - v.w );
	}

	Vector4 operator * ( const Vector4& v ) const
	{
		return Vector4( x * v.x, y * v.y, z * v.z, w * v.w );
	}
};