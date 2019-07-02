#include<math.h>
#include"Transform.h"
#include"Stream.h"

#define PI 3.1415926

void Transform::Init(float w, float h)
{
	mWidth = w;
	mHeight = h;

	float aspect = w / h;
	SetPerspective(0.5f*PI, aspect, 1.0f, 600.0f);
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
	Matrix4D tmp;
	Matrix4D::Multiply(mWorld, mView, tmp);

	Stream::PrintMatrix4D(tmp, "tmp");

	Matrix4D::Multiply(tmp, mProject, mWVP);

	Stream::PrintMatrix4D(mView, "mView");
	Stream::PrintMatrix4D(mProject, "mProject");
	Stream::PrintMatrix4D(mWVP, "WVP");
}

void Transform::ApplyTransform(Vector4& vout, const Vector4& vin)
{
	Matrix4D::MulRight(vout, vin, mWVP);
}

//归一化得到屏幕坐标
void Transform::Homogenize(Vector4 &v1)
{
	//std::cout <<  v1.x << "!" << v1.y << "!" << v1.z<< "!" << v1.w << "\n";
	float w = 1.0f / v1.w;
	v1.x = (v1.x * w + 1.0f) * mWidth * 0.5f;
	v1.y = (-v1.y * w + 1.0f) * mHeight * 0.5f;
	v1.z *= w;
	v1.w = 1.0f;
	//std::cout << "@@" << v1.x << "@@" << v1.y << "@@" << v1.z << "@@"<< v1.w << "\n";
}