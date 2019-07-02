
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
	for (int i = 0; i < mHeight; i++)
	{
		for (int j = 0; j < mWidth; j++)
			mFrameBuffer[i][j] = 0;
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
	mTransform->ApplyTransform(sp, start.mPos);
	mTransform->Homogenize(sp);

	Vector4 ep = end.mPos;
	mTransform->ApplyTransform(ep, end.mPos);
	mTransform->Homogenize(ep);

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
	DrawLineDDA(v1, v2);
	DrawLineDDA(v3, v2);
	DrawLineDDA(v1, v3);
}