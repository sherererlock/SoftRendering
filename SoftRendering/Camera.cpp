#include"camera.h"

Matrix4D Camera::LookAt()
{
	Vector3 forward = (mEye - mLook).Normorlize();
	Vector3 right = mUp.Cross(forward);
	Vector3 up = forward.Cross(right);

	Matrix4D camToWorld;

	camToWorld.mMat[0][0] = right.x;
	camToWorld.mMat[0][1] = right.y;
	camToWorld.mMat[0][2] = right.z;
	camToWorld.mMat[1][0] = mUp.x;
	camToWorld.mMat[1][1] = mUp.y;
	camToWorld.mMat[1][2] = mUp.z;
	camToWorld.mMat[2][0] = forward.x;
	camToWorld.mMat[2][1] = forward.y;
	camToWorld.mMat[2][2] = forward.z;

	camToWorld.mMat[3][0] = mEye.x;
	camToWorld.mMat[3][1] = mEye.y;
	camToWorld.mMat[3][2] = mEye.z;

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