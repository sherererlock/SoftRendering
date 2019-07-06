#pragma once
#include "Light.h"

Color Light::CalcDiffuse(const Light& light, const Vertex& vertex)
{
	Color diff = light.mColor;
	Vector4 dir = ( light.mPos - vertex.mPos ).Normorlize( );
	float cos = ::fmaxf( Vector4::Dot(vertex.mNormal, dir), 0.0f );

	return diff * cos;
}

Color Light::CalcSpecular(const Vector4 campos, const Light& light, const Vertex& vertex, float Sharpness)
{
	Color speclur = light.mColor;
	Vector4 v = (campos - vertex.mPos).Normorlize();
	Vector4 l = (light.mPos - vertex.mPos).Normorlize();
	Vector4 h = (l + v) / (l + v).Length();

	float cos = ::fmaxf(Vector4::Dot(vertex.mNormal, h), 0.0f);
	float factor = pow(cos, Sharpness);

	return speclur * factor;
}

Color Light::CalcAmbient(const Light& light, const Vertex& vertex)
{
	return light.mColor;
}