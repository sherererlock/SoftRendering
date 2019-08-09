#pragma once
#include"Vector.h"
#include"Color.h"
#include<vector>

class Vertex
{
public:
	Vector4 mPos;
	Vector4 mNormal;
	Color	mColor;
	Vector2 mTextureUV;
	float	mReciprocalOfZ;

public:
	Vertex() { } 
	Vertex(Vector4 pos, Vector4 normal, Color color) :
		mPos(pos), mNormal(normal), mColor(color), mReciprocalOfZ(1.0f){}

	void PrepareTextureUV()
	{
		assert(mPos.w != 0.0f);
		mReciprocalOfZ = 1.0f / mPos.w;
		mTextureUV = mTextureUV * mReciprocalOfZ;
	}

	static Vertex VertexLerp(const Vertex& v1, const Vertex& v2, float lerp)
	{
		Vertex v;
		v.mPos.x = v1.mPos.x + lerp * (v2.mPos.x - v1.mPos.x);
		v.mPos.y = v1.mPos.y + lerp * (v2.mPos.y - v1.mPos.y);
		v.mPos.z = v1.mPos.z + lerp * (v2.mPos.z - v1.mPos.z);
		v.mPos.w = 1.0f;
		v.mColor.r = v1.mColor.r + lerp * (v2.mColor.r - v1.mColor.r);
		v.mColor.g = v1.mColor.g + lerp * (v2.mColor.g - v1.mColor.g);
		v.mColor.b = v1.mColor.b + lerp * (v2.mColor.b - v1.mColor.b);
		v.mTextureUV.x = v1.mTextureUV.x + lerp * (v2.mTextureUV.x - v1.mTextureUV.x);
		v.mTextureUV.y = v1.mTextureUV.y + lerp * (v2.mTextureUV.y - v1.mTextureUV.y);
		v.mReciprocalOfZ = v1.mReciprocalOfZ + lerp * (v2.mReciprocalOfZ - v1.mReciprocalOfZ);

		return v;
	}
};

struct Triangle
{
	std::vector<Vertex> mVertices;
};