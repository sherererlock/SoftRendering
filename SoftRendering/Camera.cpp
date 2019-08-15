#include"camera.h"
#include"Stream.h"

Matrix4D Camera::LookAt() const
{
	Vector3 forward = (mLook - mEye).Normalize();
	Vector3 newup = mUp;
	newup.Normalize();
	Vector3 right = Vector3::Cross(newup, forward);
	right.Normalize();
	Vector3 up = Vector3::Cross(forward, right);
	up.Normalize();

	Matrix4D camToWorld;

	//Stream::PrintVector3(forward, "forward");
	//Stream::PrintVector3(right, "right");
	//Stream::PrintVector3(up, "up");

	camToWorld.mMat[0][0] = right.x;
	camToWorld.mMat[1][0] = right.y;
	camToWorld.mMat[2][0] = right.z;

	camToWorld.mMat[0][1] = up.x;
	camToWorld.mMat[1][1] = up.y;
	camToWorld.mMat[2][1] = up.z;

	camToWorld.mMat[0][2] = forward.x;
	camToWorld.mMat[1][2] = forward.y;
	camToWorld.mMat[2][2] = forward.z;

	camToWorld.mMat[3][0] = -Vector3::Dot(right, mEye);
	camToWorld.mMat[3][1] = -Vector3::Dot(up, mEye);
	camToWorld.mMat[3][2] = -Vector3::Dot(forward, mEye);
	camToWorld.mMat[3][3] = 1.0f;

	return camToWorld;
}

void Camera::MoveForward(float value)
{

}

void Camera::MoveUp(float value)
{

}

void Camera::Rotate(float value)
{

}