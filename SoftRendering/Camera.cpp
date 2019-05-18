#include"camera.h"
#include"Stream.h"

Matrix4D Camera::LookAt() const
{
	Vector3 forward = (mLook - mEye).Normorlize();
	Vector3 newup = mUp;
	newup.Normorlize();
	Vector3 right = newup.Cross(forward);
	right.Normorlize();
	Vector3 up = forward.Cross(right);
	up.Normorlize();

	Matrix4D camToWorld;

	Stream::PrintVector3(forward, "forward");
	Stream::PrintVector3(right, "right");
	Stream::PrintVector3(up, "up");

	camToWorld.mMat[0][0] = right.x;
	camToWorld.mMat[0][1] = right.y;
	camToWorld.mMat[0][2] = right.z;
	camToWorld.mMat[1][0] = up.x;
	camToWorld.mMat[1][1] = up.y;
	camToWorld.mMat[1][2] = up.z;
	camToWorld.mMat[2][0] = forward.x;
	camToWorld.mMat[2][1] = forward.y;
	camToWorld.mMat[2][2] = forward.z;

	camToWorld.mMat[3][0] = -right.Dot(mEye);
	camToWorld.mMat[3][1] = -up.Dot(mEye);
	camToWorld.mMat[3][2] = -forward.Dot(mEye);

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