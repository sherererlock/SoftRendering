#pragma once
#include "Color.h"
#include "Vector.h"
#include "Vertex.h"

class Light
{
public:
	Vector4		mPos;
	Vector3		mIntensity;
	int			mType;

	enum
	{
		_Light_Point,
		_Light_Directional,
		_Light_Ambient
	};

public:
	static Vector3 CalcDiffuse(const Light& light, const Vertex& vertex);
	static Vector3 CalcSpecular(const Vector4 campos, const Light& light, const Vertex& vertex, float sharpness = 1.0f);
	static Vector3 CalcAmbient( );
};