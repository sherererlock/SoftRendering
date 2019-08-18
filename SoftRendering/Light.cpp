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

	float length = (vertex.mNormal.Length() * dir.Length());
	float cos = ::fmaxf( Vector4::Dot(vertex.mNormal, dir)/ length, 0.0f );

	return diff * cos;
}

Vector3 Light::CalcSpecular(const Vector4 campos, const Light& light, const Vertex& vertex, float sharpness)
{
	Vector3 speclur = light.mIntensity;

	Vector4 dir;
	if (light.mType == Light::_Light_Point)
		dir = (light.mPos - vertex.mPos);
	else if (light.mType == Light::_Light_Directional)
		dir = light.mPos;

	dir.Normalize();
	Vector4 v = (campos - vertex.mPos).Normalize();
	Vector4 reflection = vertex.mNormal * 2 * Vector4::Dot(vertex.mNormal, dir) - dir;

	float dot = Vector4::Dot(vertex.mNormal, reflection);
	if (dot > 0)
	{
		float cos = dot / (vertex.mNormal.Length()*reflection.Length());
		float factor = pow(cos, sharpness);

		return speclur * factor;
	}

	return Vector3(0.0f, 0.0f, 0.0f);
}
