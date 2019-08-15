#pragma once
#include "Light.h"

Vector3 Light::CalcDiffuse(const Light& light, const Vertex& vertex)
{
	Vector3 diff = light.mIntensity;
	Vector4 dir;
	if (light.mType == Light::_Light_Point)
		dir = (light.mPos - vertex.mPos).Normalize();
	else if (light.mType == Light::_Light_Directional)
		dir = light.mPos;

	float cos = ::fmaxf( Vector4::Dot(vertex.mNormal, dir), 0.0f );

	return diff * cos;
}

Vector3 Light::CalcSpecular(const Vector4 campos, const Light& light, const Vertex& vertex, float sharpness)
{
	Vector3 speclur = light.mIntensity;

	Vector4 dir;
	if (light.mType == Light::_Light_Point)
		dir = (light.mPos - vertex.mPos).Normalize();
	else if (light.mType == Light::_Light_Directional)
		dir = light.mPos;

	Vector4 v = (campos - vertex.mPos).Normalize();
	Vector4 h = (dir + v) / (dir + v).Length();

	float cos = ::fmaxf(Vector4::Dot(vertex.mNormal, h), 0.0f);
	float factor = pow(cos, sharpness);

	return speclur * factor;
}
