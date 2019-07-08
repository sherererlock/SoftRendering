
#include<math.h>
#include<iostream>
#include"Device.h"
#include"DrawBoard.h"
#include"Stream.h"

#define Round(x) (int((x)+0.5f))

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

	memset(mZBuffer, 0, h * w);

	mCamera.mEye = Vector3(-5.0f, 50.0f, -5.0f);
	mCamera.mLook = Vector3(50.0f, 50.0f, 50.0f);
	mCamera.mUp	= Vector3(0.0f, 100.0f, 0.0f);

	mTransform = new Transform();
	mTransform->SetView(mCamera);
	mTransform->Init(w, h);
	mTransform->UpdateTransform();
}

void Device::ClearBuffer()
{
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			mFrameBuffer[y][x] = 0;
			mZBuffer[y*mWidth + x] = 0.0f;
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

void Device::DrawPoint(const Vector3& point, const Color& color)
{
	int x = Round(point.x);
	int y = Round(point.y);
	int r = Round(color.r);
	int g = Round(color.g);
	int b = Round(color.b);
	if (x > mWidth || x < 0 || y < 0 || y > mHeight)
		return;

	// Éî¶È²âÊÔ
	if (point.z > mZBuffer[y * mWidth + x])
		return;

	mFrameBuffer[y][x] = r << 16 | g << 8 | b;
}

void Device::DrawPoint3D(const Vector3& point, const Color& color)
{
	Vector4 v;
	mTransform->ApplyTransform(v, Vector4(point.x, point.y, point.z, 1.0f));
	mTransform->Homogenize(v);

	//Stream::PrintVector3(Vector3(v.x, v.y, v.z), "3dpoint");
	DrawPoint(Vector3(v.x, v.y, v.z), color);
}

void Device::DrawLineDDA(const Vertex& start, const Vertex& end)
{
	Vector4 sp = start.mPos;
	Vector4 ep = end.mPos;

	Color sc = start.mColor;
	Color ec = end.mColor;

	float r = ec.r - sc.r;
	float g = ec.g - sc.g;
	float b = ec.b - sc.b;
	float a = ec.a - sc.a;

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

		for (int i = 0; i < steps; i++)
		{ 
			Color color(sc.r + deltar * i, sc.g + deltag * i, sc.b + deltag * i, sc.a + deltaa * i);
			DrawPoint(Vector3(x, y, 0.0f), color);
			y += deltay * i;
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

		for (int i = 0; i < steps; i++)
		{
			Color color(sc.r + deltar * i, sc.g + deltag * i, sc.b + deltag * i, sc.a + deltaa * i);
			DrawPoint(Vector3(x, y, 0.0f), color);
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

		for (int i = 0; i <= steps; i++)
		{
			Color color(sc.r + deltar * i, sc.g + deltag * i, sc.b + deltag * i, sc.a + deltaa * i);
			DrawPoint(Vector3(x, y, 0.0f), color);
			x += deltay / k;
			y += deltay;

			if (x< 0 || x > mWidth || y < 0 || y > mHeight)
				break;
		}
	}
}

void Device::DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	if (CheckBackCull(v1, v2, v3))
		return;

	Vertex newv1 = v1;
	Vertex newv2 = v2;
	Vertex newv3 = v3;

	mTransform->ApplyTransform(newv1.mPos, v1.mPos);
	mTransform->Homogenize(newv1.mPos);

	mTransform->ApplyTransform(newv2.mPos, v2.mPos);
	mTransform->Homogenize(newv2.mPos);

	mTransform->ApplyTransform(newv3.mPos, v3.mPos);
	mTransform->Homogenize(newv3.mPos);

	FillTriangle(newv1, newv2, newv3);

	DrawLineDDA(newv1, newv2);
	DrawLineDDA(newv3, newv2);
	DrawLineDDA(newv1, newv3);
}

Vertex Vertexlerp(const Vertex& v1, const Vertex& v2, float lerp)
{
	Vertex v;
	v.mPos.x = v1.mPos.x + lerp * (v2.mPos.x - v1.mPos.x);
	v.mPos.y = v1.mPos.y + lerp * (v2.mPos.y - v1.mPos.y);
	v.mPos.z = v1.mPos.z + lerp * (v2.mPos.z - v1.mPos.z);
	v.mPos.w = 1.0f;
	v.mColor.r = v1.mColor.r + lerp * (v2.mColor.r - v1.mColor.r);
	v.mColor.g = v1.mColor.g + lerp * (v2.mColor.g - v1.mColor.g);
	v.mColor.b = v1.mColor.b + lerp * (v2.mColor.b - v1.mColor.b);
	v.mNormal = v1.mNormal;

	return v;
}

void Device::FillTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	//if (CheckBackCull(v1, v2, v3))
	//	return;

	if (v1.mPos.y == v2.mPos.y && v1.mPos.y == v3.mPos.y)
		return;

	if (v1.mPos.y == v2.mPos.y)
	{
		int y1 = (int)(v3.mPos.y + 0.5f);
		int y2 = (int)(v1.mPos.y + 0.5f);
		
		int top = min(y1, y2);
		int bottom = max(y1, y2);

		for (int i = top; i <= bottom; i++)
		{
			float lerp = (float)(i - top) / (float)(bottom - top);
			if (v3.mPos.y < v1.mPos.y)
				lerp = -lerp;
			Vertex vl = Vertexlerp(v3, v1, lerp);
			Vertex vr = Vertexlerp(v3, v2, lerp);
			vl.mPos.y = vr.mPos.y = i;
			DrawLineDDA(vl, vr);
		}
	}
	else if (v1.mPos.y == v3.mPos.y)
	{
		int y1 = (int)(v2.mPos.y + 0.5f);
		int y2 = (int)(v1.mPos.y + 0.5f);

		int top = max(y1, y2);
		int bottom = min(y1, y2);

		for (int i = bottom; i < top; i++)
		{
			float lerp = (i - bottom) / (float)(top - bottom);
			if (v2.mPos.y < v1.mPos.y)
				lerp = -lerp;
			Vertex vl = Vertexlerp(v2, v1, lerp);
			Vertex vr = Vertexlerp(v2, v3, lerp);
			vl.mPos.y = vr.mPos.y == i;
			DrawLineDDA(vl, vr);
		}
	}
	else if (v2.mPos.y == v3.mPos.y)
	{
		int y1 = (int)(v3.mPos.y + 0.5f);
		int y2 = (int)(v1.mPos.y + 0.5f);

		int top = max(y1, y2);
		int bottom = min(y1, y2);

		for (int i = bottom; i < top; i++)
		{
			float lerp = (i - bottom) / (float)(top - bottom);
			if (v1.mPos.y < v2.mPos.y)
				lerp = -lerp;
			Vertex vl = Vertexlerp(v1, v2, lerp);
			Vertex vr = Vertexlerp(v1, v3, lerp);
			vl.mPos.y = vr.mPos.y == i;
			DrawLineDDA(vl, vr);
		}
	}
	else
	{
		Vertex middle = v1;
		Vertex top = v2;
		Vertex bottom = v3;

		float y = min(v1.mPos.y, v2.mPos.y);
		y = max(y, v3.mPos.y);

		if (y == v2.mPos.y)
		{
			middle = v2;
			if (v1.mPos.y > v3.mPos.y)
			{
				top = v1;
				bottom = v3;
			}
			else
			{
				top = v3;
				bottom = v1;
			}
		}
		else if (y == v3.mPos.y)
		{
			middle = v3;
			if (v1.mPos.y > v2.mPos.y)
			{
				top = v1;
				bottom = v2;
			}
			else
			{
				top = v2;
				bottom = v1;
			}
		}
		else
		{
			if (v2.mPos.y > v3.mPos.y)
			{
				top = v2;
				bottom = v3;
			}
			else
			{
				top = v3;
				bottom = v2;
			}
		}

		float lerp = (float)(middle.mPos.y - bottom.mPos.y) / (float)(top.mPos.y - bottom.mPos.y);
		Vertex mp = Vertexlerp(bottom, top, lerp);

		FillTriangle(top, middle, mp);
		FillTriangle(middle, mp, bottom);
	}

}

bool Device::CheckBackCull(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
{
	Vector4 vec1 = v2.mPos - v1.mPos;
	Vector4 vec2 = v3.mPos - v2.mPos;
	Vector4 normal = Vector4::Cross( vec1, vec2 );

	return normal.z > 0;
}  