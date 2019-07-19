
#include<math.h>
#include<iostream>
#include"Device.h"
#include"DrawBoard.h"
#include"Stream.h"

#define Round(x) (int((x)+0.5f))
#define PI 3.1415926

void Device::Init(int w, int h)
{
	mWidth = w;
	mHeight = h;
	mDrawBoard = new DrawBoard();
	mDrawBoard->Init(w, h);
	int* fb = (int*)mDrawBoard->GetFramebuffer();
	mFrameBuffer = (int**)malloc(h * sizeof(int*));

	for (int i = 0; i < h; i++)
		mFrameBuffer[i] = fb + i * w;

	mZBuffer = new float[h * w];

	memset(mZBuffer, 1, h * w);

	mCamera.mEye = Vector3(-5.0f, 50.0f, -5.0f);
	mCamera.mLook = Vector3(50.0f, 50.0f, 50.0f);
	mCamera.mUp	= Vector3(0.0f, 100.0f, 0.0f);
	mCamera.mNear = 1.0f;
	mCamera.mFar = 600.f;
	mCamera.mFov = 0.5f*PI;

	mTransform = new Transform();
	mTransform->Init(w, h);
	mTransform->SetView(mCamera);
	mTransform->SetPerspective(0.5f*PI, (float)w / (float)h, mCamera.mNear, mCamera.mFar);
	mTransform->UpdateTransform();

	InitPlane();

	mAmbient.mColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
	mAmbient.mPos = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	mPoint.mColor = Color(255.0f, 255.0f, 255.0f, 255.0f);
	mPoint.mPos = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	mSky.mColor = Color(255.0f, 255.0f, 255.0f, 255.0f);
	mSky.mPos = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

void Device::InitPlane()
{
	// near plane
	mPlanes.push_back(Vector4(0, 0, 1, -1.0f));
	// far plane
	mPlanes.push_back(Vector4(0, 0, -1,600.0f));

	// left plane

	// right plane

	// top plane

	// bottom plane
}

void Device::ClearBuffer()
{
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			mFrameBuffer[y][x] = 0;
			mZBuffer[y*mWidth + x] = 1.0f;
		}
	}
}

void Device::Close()
{
	if (mFrameBuffer != NULL)
	{
		free(mFrameBuffer);
		mFrameBuffer = NULL;
	}

	if(mDrawBoard!=NULL)
		mDrawBoard->Close();

	delete mDrawBoard;
	delete mTransform;
}

void Device::DrawPoint(const Vector3& point, const Color& color) const
{
	int x = Round(point.x);
	int y = Round(point.y);
	int r = Round(color.r);
	int g = Round(color.g);
	int b = Round(color.b);
	if (x > mWidth || x < 0 || y < 0 || y > mHeight)
		return;

	// Éî¶È²âÊÔ
	//Stream::PrintVector3(Vector3(point.z, point.z, point.z), "point");
	//Stream::PrintVector3(Vector3(mZBuffer[y * mWidth + x], mZBuffer[y * mWidth + x], mZBuffer[y * mWidth + x]), "zbuff");
	if (point.z > mZBuffer[y * mWidth + x])
		return;
	else
		mZBuffer[y * mWidth + x] = point.z;

	mFrameBuffer[y][x] = r << 16 | g << 8 | b;
}

void Device::DrawPoint3D(const Vector3& point, const Color& color) const
{
	Vector4 v;
	mTransform->TransformToProjectSpace(v, Vector4(point.x, point.y, point.z, 1.0f));
	mTransform->TransformToScreenSpace(v);

	//Stream::PrintVector3(Vector3(v.x, v.y, v.z), "3dpoint");
	DrawPoint(Vector3(v.x, v.y, v.z), color);
}

void Device::DrawLine(const Vertex& start, const Vertex& end) const
{
	Vector4 sp = start.mPos;
	Vector4 ep = end.mPos;

	float dx = abs(ep.x - sp.x);
	float dy = abs(ep.y - sp.y);

	if (dx > dy)
	{	
		const Vertex& left = (ep.x > sp.x) ? start : end;
		const Vertex& right = (ep.x > sp.x) ? end : start;

		for (int i = left.mPos.x; i < right.mPos.x; i++)
		{
			float lerp = (i - left.mPos.x) / (right.mPos.x - left.mPos.x);
			Vertex vertex = Vertex::VertexLerp(left, right, lerp);
			DrawPoint(Vector3(vertex.mPos.x, vertex.mPos.y, vertex.mPos.z ) , vertex.mColor);
		}
	}
	else
	{
		const Vertex& down = (ep.y > sp.y) ? start : end;
		const Vertex& up = (ep.y > sp.y) ? end : start;

		for (int i = down.mPos.x; i < up.mPos.x; i++)
		{
			float lerp = (i - down.mPos.x) / (up.mPos.x - down.mPos.x);
			Vertex vertex = Vertex::VertexLerp(down, up, lerp);
			DrawPoint(Vector3(vertex.mPos.x, vertex.mPos.y, vertex.mPos.z), vertex.mColor);
		}
	}
}

// a  bug function
void Device::DrawLineDDA(const Vertex& start, const Vertex& end) const
{
	Vector4 sp = start.mPos;
	Vector4 ep = end.mPos;

	if (sp.x == ep.x && sp.y == ep.y)
		return;

	Color sc = start.mColor;
	Color ec = end.mColor;

	float r = ec.r - sc.r;
	float g = ec.g - sc.g;
	float b = ec.b - sc.b;
	float a = ec.a - sc.a;

	float z = ep.z - sp.z;

	float x = sp.x;
	float y = sp.y;

	if (sp.x == ep.x)
	{
		float deltay = sp.y > ep.y ? -1.0f : 1.0f;
		int steps = abs(Round(sp.y - ep.y));

		float deltar = r / steps;
		float deltag = g / steps;
		float deltab = b / steps;
		float deltaa = a / steps;

		float deltaz = z / steps;

		for (int i = 0; i < steps; i++)
		{ 
			Color color(sc.r + deltar * i, sc.g + deltag * i, sc.b + deltab * i, sc.a + deltaa * i);
			float pointz = sp.z + deltaz * i;
			DrawPoint(Vector3(x, y, pointz), color);
			y += deltay;
			if (y < 0 || y > mHeight)
				break;
		}

		return;
	}

	float k = (sp.y - ep.y) / (sp.x - ep.x);
	if (abs(k) <= 1)
	{
		int steps = abs(Round(sp.x - ep.x));
		float deltax = sp.x > ep.x ? -1 : 1;

		float deltar = r / steps;
		float deltag = g / steps;
		float deltab = b / steps;
		float deltaa = a / steps;

		float deltaz = z / steps;

		for (int i = 0; i < steps; i++)
		{
			Color color(sc.r + deltar * i, sc.g + deltag * i, sc.b + deltab * i, sc.a + deltaa * i);
			float pointz = sp.z + deltaz * i;
			DrawPoint(Vector3(x, y, pointz), color);
			x += deltax;
			y += k * deltax;

			if (x< 0 || x > mWidth || y < 0 || y > mHeight)
				break;
		}
	}
	else
	{
		int steps = abs(Round(sp.y - ep.y));
		float deltay = sp.y > ep.y ? -1 : 1;

		float deltar = r / steps;
		float deltag = g / steps;
		float deltab = b / steps;
		float deltaa = a / steps;

		float deltaz = z / steps;

		for (int i = 0; i <= steps; i++)
		{
			Color color(sc.r + deltar * i, sc.g + deltag * i, sc.b + deltab * i, sc.a + deltaa * i);
			float pointz = sp.z + deltaz * i;
			DrawPoint(Vector3(x, y, pointz), color);
			x += deltay / k;
			y += deltay;

			if (x< 0 || x > mWidth || y < 0 || y > mHeight)
				break;
		}
	}
}

void Device::DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
{
	if (CheckBackCull(v1, v2, v3))
		return;

	Vertex newv1 = v1;
	Vertex newv2 = v2;
	Vertex newv3 = v3;

	//LightShader(newv1, mPoint);
	//LightShader(newv1, mSky);

	//LightShader(newv2, mPoint);
	//LightShader(newv2, mSky);

	//LightShader(newv3, mPoint);
	//LightShader(newv3, mSky);

	mTransform->TransformToProjectSpace(newv1.mPos, v1.mPos);
	mTransform->TransformToScreenSpace(newv1.mPos);

	mTransform->TransformToProjectSpace(newv2.mPos, v2.mPos);
	mTransform->TransformToScreenSpace(newv2.mPos);

	mTransform->TransformToProjectSpace(newv3.mPos, v3.mPos);
	mTransform->TransformToScreenSpace(newv3.mPos);

	DrawLineDDA(newv1, newv2);
	DrawLineDDA(newv3, newv2);
	DrawLineDDA(newv1, newv3);
}

void Device::FillTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
{
	if (CheckBackCull(v1, v2, v3))
		return;

	Vertex newv1 = v1;
	Vertex newv2 = v2;
	Vertex newv3 = v3;

	//LightShader(newv1, mPoint);
	//LightShader(newv1, mSky);

	//LightShader(newv2, mPoint);
	//LightShader(newv2, mSky);

	//LightShader(newv3, mPoint);
	//LightShader(newv3, mSky);

	mTransform->TransformToViewSpace(newv1.mPos, v1.mPos);
	mTransform->TransformToProjectSpace(newv1.mPos, newv1.mPos);
	mTransform->TransformToScreenSpace(newv1.mPos);

	mTransform->TransformToViewSpace(newv2.mPos, v2.mPos);
	mTransform->TransformToProjectSpace(newv2.mPos, newv2.mPos);
	mTransform->TransformToScreenSpace(newv2.mPos);

	mTransform->TransformToViewSpace(newv3.mPos, v3.mPos);
	mTransform->TransformToProjectSpace(newv3.mPos, newv3.mPos);
	mTransform->TransformToScreenSpace(newv3.mPos);

	if (newv1.mPos.y == newv2.mPos.y && newv1.mPos.y == newv3.mPos.y)
		return;

	FillTriangleHelper(newv1, newv2, newv3);
}

void Device::FillTriangleHelper1(Vertex& newv1, Vertex& newv2, Vertex& newv3) const
{
	int y1 = (int)(newv3.mPos.y + 0.5f);
	int y2 = (int)(newv1.mPos.y + 0.5f);

	int top = min(y1, y2);
	int bottom = max(y1, y2);

	bool up = newv3.mPos.y < newv1.mPos.y;
	for (int i = top; i <= bottom; i++)
	{
		float lerp = (float)(i - top) / (float)(bottom - top);
		Vertex vl, vr;
		if (up)
		{
			vl = Vertex::VertexLerp(newv3, newv1, lerp);
			vr = Vertex::VertexLerp(newv3, newv2, lerp);
		}
		else
		{
			vl = Vertex::VertexLerp(newv1, newv3, lerp);
			vr = Vertex::VertexLerp(newv2, newv3, lerp);
		}

		vl.mPos.y = vr.mPos.y = i;

		DrawLine(vl, vr);
	}
}

void Device::FillTriangleHelper(Vertex& newv1, Vertex& newv2, Vertex& newv3) const
{
	if (newv1.mPos.y == newv2.mPos.y)
	{
		FillTriangleHelper1(newv1, newv2, newv3);
	}
	else if (newv1.mPos.y == newv3.mPos.y)
	{
		FillTriangleHelper1(newv1, newv3, newv2);
	}
	else if (newv2.mPos.y == newv3.mPos.y)
	{
		FillTriangleHelper1(newv2, newv3, newv1);
	}
	else
	{
		Vertex middle = newv1;
		Vertex top = newv2;
		Vertex bottom = newv3;

		float y = min(newv1.mPos.y, newv2.mPos.y);
		y = max(y, newv3.mPos.y);

		if (y == newv2.mPos.y)
		{
			middle = newv2;
			if (newv1.mPos.y > newv3.mPos.y)
			{
				top = newv1;
				bottom = newv3;
			}
			else
			{
				top = newv3;
				bottom = newv1;
			}
		}
		else if (y == newv3.mPos.y)
		{
			middle = newv3;
			if (newv1.mPos.y > newv2.mPos.y)
			{
				top = newv1;
				bottom = newv2;
			}
			else
			{
				top = newv2;
				bottom = newv1;
			}
		}
		else
		{
			if (newv2.mPos.y > newv3.mPos.y)
			{
				top = newv2;
				bottom = newv3;
			}
			else
			{
				top = newv3;
				bottom = newv2;
			}
		}

		float lerp = (float)(middle.mPos.y - bottom.mPos.y) / (float)(top.mPos.y - bottom.mPos.y);
		Vertex mp = Vertex::VertexLerp(bottom, top, lerp);

		FillTriangleHelper(top, middle, mp);
		FillTriangleHelper(middle, bottom, mp);
	}
}

void Device::DrawQuadrangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) const
{
	//DrawTriangle(v1, v2, v3);
	//DrawTriangle(v1, v3, v4);
}

void Device::FillQuadrangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) const
{
	FillTriangle(v1, v2, v3);
	FillTriangle(v1, v3, v4);
}

void Device::FrustumCulling(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
{

}

bool Device::CheckBackCull(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
{
	Vector4 vec1 = v2.mPos - v1.mPos;
	Vector4 vec2 = v3.mPos - v1.mPos;
	Vector4 normal = Vector4::Cross( vec1, vec2 );

	return normal.z < 0;
}

void Device::LightShader(Vertex& vertex, const Light& light) const
{
	Vector4 campos(mCamera.mEye.x, mCamera.mEye.y, mCamera.mEye.z, 1.0f);
	Color specular = Light::CalcSpecular(campos, light, vertex);
	Color diffuse = Light::CalcDiffuse(light, vertex);
	Color ambient = Light::CalcAmbient(light, vertex);

	vertex.mColor = vertex.mColor * (specular + diffuse + ambient);

	vertex.mColor.r = vertex.mColor.r > 255.0f ? 255.0f : 255.0f;
	vertex.mColor.g = vertex.mColor.g > 255.0f ? 255.0f : 255.0f;
	vertex.mColor.b = vertex.mColor.b > 255.0f ? 255.0f : 255.0f;
	vertex.mColor.a = vertex.mColor.a > 255.0f ? 255.0f : 255.0f;
}

void Device::MoveCameraForwardOrBackward(float dis)
{
	Vector3 forward = (mCamera.mLook - mCamera.mEye).Normorlize();
	mCamera.mEye = mCamera.mEye + forward * dis;
	mCamera.mLook = mCamera.mLook + forward * dis;

	mTransform->SetView(mCamera);
	mTransform->UpdateTransform();
}

void Device::MoveCameraRightOrLeft(float dis)
{
	Vector3 forward = (mCamera.mLook - mCamera.mEye).Normorlize();
	Vector3 up = mCamera.mUp.Normorlize();
	Vector3 right = Vector3::Cross(up, forward);

	mCamera.mEye = mCamera.mEye + right * dis;
	mCamera.mLook = mCamera.mLook + right * dis;

	mTransform->SetView(mCamera);
	mTransform->UpdateTransform();
}

void Device::MoveCameraUpOrDown(float dis)
{
	Vector3 forward = (mCamera.mLook - mCamera.mEye).Normorlize();
	Vector3 nup = mCamera.mUp.Normorlize();
	Vector3 right = Vector3::Cross(nup, forward);
	right.Normorlize();
	Vector3 up = Vector3::Cross(forward, right);
	up.Normorlize();

	mCamera.mEye = mCamera.mEye + up * dis;
	mCamera.mLook = mCamera.mLook + up * dis;

	mTransform->SetView(mCamera);
	mTransform->UpdateTransform();
}