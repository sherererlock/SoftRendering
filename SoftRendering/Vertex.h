#pragma once
#include"Vector.h"
#include"Color.h"

class Vertex
{
public:
	Vector3 mPos;
	Vector3 mNormal;
	Color	mColor;

public:
	Vertex() {} 
	Vertex(Vector3 pos, Vector3 normal, Color color) :
		mPos(pos), mNormal(normal), mColor(color) {}
};