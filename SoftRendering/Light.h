#pragma once
#include "Color.h"
#include "Vector.h"
#include "Vertex.h"

class Light
{
public:
	Vector4		mPos;
	Color		mColor;

public:
	static Color CalcDiffuse(const Light& light, const Vertex& vertex);
	static Color CalcSpecular(const Vector4 campos, const Light& light, const Vertex& vertex, float Sharpness = 1.0f);
	static Color CalcAmbient(const Light& light, const Vertex& vertex);
};