#pragma once
#include"Matrix.h"
#include"Camera.h"
#include"Vector.h"

class Transform
{
private:
	Matrix4D	mWorld;
	Matrix4D	mView;
	Matrix4D	mProject;
	Matrix4D	mWV;
	Matrix4D	mWVP;

	float		mWidth;
	float		mHeight;

public:
	Transform() : mWidth(800.0f), mHeight(600.0f){ }
	~Transform() {}
	void Init(float w, float h);
	void SetView(const Camera& cam);
	void SetPerspective(float fov, float aspect, float znear, float zfar);
	void UpdateTransform();
	void TransformToViewSpace(Vector4& vout, const Vector4& vin);
	void TransformToProjectSpace(Vector4& vout, const Vector4& vin);
	void TransformToScreenSpace(Vector4 &v1);
};
