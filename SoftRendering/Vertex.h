#pragma once
#include"Vector.h"
#include"Color.h"

class Vertex
{
public:
	Vector4 mPos;
	Vector4 mNormal;
	Color	mColor;

public:
	Vertex() {} 
	Vertex(Vector4 pos, Vector4 normal, Color color) :
		mPos(pos), mNormal(normal), mColor(color) {}
};

struct Triangle
{

};