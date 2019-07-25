#pragma once
#include"Vector.h"

class Color
{
public:
	float r, g, b, a;

	Color( ) { }
	Color(float r, float g, float b, float a ) : r(r), g(g), b(b), a(a) { }

	Color operator* (const Color& color) const
	{
		return Color(r * color.r, g * color.g, b * color.b, a * color.a);
	}

	Color operator* (float factor) const
	{
		return Color(r * factor, g * factor, b * factor, a * factor);
	}

	Color operator+ (const Color& color) const
	{
		return Color(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	Color operator* (const Vector3& intesity) const
	{
		return Color(r * intesity.x, g * intesity.y, b * intesity.z, a);
	}
};
