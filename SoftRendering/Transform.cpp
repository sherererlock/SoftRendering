#include<math.h>
#include"Transform.h"
#include"Stream.h"

void Transform::Init(float w, float h)
{
	mWidth = w;
	mHeight = h;
}

void Transform::SetView(const Camera& cam)
{
	mView = cam.LookAt();
}

void Transform::SetPerspective(float fov, float aspect, float znear, float zfar)
{
	float cot = 1.0f / tan(fov*0.5f);
	float fsubn = 1.0f / (zfar - znear);
	mProject = Matrix4D(
		cot / aspect, 0.0f, 0.0f, 0.0f,
		0.0f, cot, 0.0f, 0.0f,
		0.0f, 0.0f, zfar * fsubn, 1.0f,
		0.0f, 0.0f, -znear * zfar * fsubn, 0.0f
	);
}

void Transform::UpdateTransform()
{
	Matrix4D::Multiply(mWorld, mView, mWV);

	//Stream::PrintMatrix4D(mWV, "tmp");

	Matrix4D::Multiply(mWV, mProject, mWVP);

	//Stream::PrintMatrix4D(mView, "mView");
	//Stream::PrintMatrix4D(mProject, "mProject");
	//Stream::PrintMatrix4D(mWVP, "WVP");
}

void Transform::TransformToViewSpace(Vector4& vout, const Vector4& vin)
{
	Matrix4D::MulRight(vout, vin, mWV);
}

void Transform::TransformToProjectSpace(Vector4& vout, const Vector4& vin)
{
	Matrix4D::MulRight(vout, vin, mProject);
}

//×ª»»µ½NDC¿Õ¼ä
void Transform::TransformToScreenSpace(Vector4 &v1)
{
	//std::cout <<  v1.x << "!" << v1.y << "!" << v1.z<< "!" << v1.w << "\n";
	float w = 1.0f / v1.w;
	v1.x = (v1.x * w + 1.0f) * mWidth * 0.5f;
	v1.y = (-v1.y * w + 1.0f) * mHeight * 0.5f;
	v1.z *= w;
	v1.w = 1.0f;
	//std::cout << "@@" << v1.x << "@@" << v1.y << "@@" << v1.z << "@@"<< v1.w << "\n";
}