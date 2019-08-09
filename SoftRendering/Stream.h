#pragma once
#include<iostream>
#include"Vector.h"
#include"Matrix.h"

class Stream
{
public:
	static void PrintInfo(std::string tag);
	static void PrintVector2(const Vector2& v, std::string tag);
	static void PrintVector3(const Vector3& v, std::string tag);
	static void PrintVector4(const Vector4& v, std::string tag);
	static void PrintMatrix4D(const Matrix4D& mat, std::string tag);
};