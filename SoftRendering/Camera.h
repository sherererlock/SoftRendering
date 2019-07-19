#pragma once

#include"vector.h"
#include"Matrix.h"

class Camera
{
public:
	Vector3 mLook;
	Vector3 mEye;
	Vector3 mUp;
	float	mNear;
	float	mFar;
	float	mFov;

public:
	Camera( ) : mUp( Vector3(0,1,0) ), mNear(0.0f), mFar(0.0f), mFov(0.0f){ }
	Camera( Vector3 look, Vector3 eye, Vector3 up ) : mLook( look ), mEye( eye ), mUp( up ), mNear(0.0f), mFar(0.0f), mFov(0.0f) { }

	Matrix4D LookAt( ) const;
	void MoveForward( float value );
	void MoveUp( float value );
	void Rotate( float value );
};
