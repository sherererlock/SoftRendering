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

	Vector2 operator + ( const Vector2& v ) const
	{
		return Vector2( x + v.x, y + v.y );
	}

	Vector2 operator - ( const Vector2& v ) const
	{
		return Vector2( x - v.x, y - v.y );
	}

	Vector2 operator * (float v) const
	{
		return Vector2(x * v, y * v);
	}

	Vector2 operator * ( const Vector2& v ) const
	{
		return Vector2( x * v.x, y * v.y );
	}

	inline static float Dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline static float Cross(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
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
		return ::sqrt(x * x + y * y + z * z);
	}

	inline Vector3& Normorlize()
	{
		float length = Length();
		assert(length > 0);
		x /= length; y /= length; z /= length;
		return *this;
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

	Vector3 operator * (float v) const
	{
		return Vector3(x * v, y * v, z * v);
	}

	inline static float Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	inline static Vector3 Cross(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
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

	Vector4 operator * (float v) const
	{
		return Vector4(x * v, y * v, z * v, w * v);
	}

	Vector4 operator / (float n) const
	{
		return Vector4(x / n, y / n, z / n, w / n);
	}

	inline static float Dot(const Vector4& v1, const Vector4& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	inline static Vector4 Cross(const Vector4& v1, const Vector4& v2)
	{
		return Vector4(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x, 1.0f);
	}
};