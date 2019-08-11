
#include<math.h>
#include<iostream>
#include"Device.h"
#include"DrawBoard.h"
#include"Stream.h"
#include"ClippingPlane.h"


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
	InitLight();

	LoadImageBuffer("test1.bmp");
}

void Device::InitPlane()
{
	// near plane
	mNearPlane = Vector4(0, 0, 1, -mCamera.mNear);
	// far plane
	mFarPlane = Vector4(0, 0, -1, mCamera.mFar);

	// left plane
	// 

	// right plane

	// top plane

	// bottom plane
}

void Device::InitLight()
{
	mAmbientLight.mIntensity = Vector3(0.5f, 0.5f, 0.5f);
	mAmbientLight.mType = Light::_Light_Ambient;

	mPointLight.mIntensity = Vector3(1.0f, 1.0f, 1.0f);
	mPointLight.mPos = Vector4(50.0f, 200.0f, 50.0f, 1.0f);
	mPointLight.mType = Light::_Light_Point;

	mDirectionalLight.mIntensity = Vector3(1.0f, 1.0f, 1.0f);
	mDirectionalLight.mPos = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	mDirectionalLight.mType = Light::_Light_Directional;
}

void Device::LoadImageBuffer(std::string resname)
{
	if (mTextureBuffer != NULL)
	{
		for (int i = 0; i < mTextureHeight; i++)
			delete mTextureBuffer[i];

		delete mTextureBuffer;

		mTextureBuffer = NULL;
	}

	HBITMAP bitmap = (HBITMAP)LoadImageA(NULL, resname.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (bitmap == NULL)
	{
		Stream::PrintInfo("Load image:" + resname + " failed");
		return;
	}

	HDC hdc = CreateCompatibleDC(NULL);

	BITMAP bmp;
	GetObject(bitmap, sizeof(BITMAP), &bmp);
	mTextureHeight = bmp.bmHeight;
	mTextureWidth = bmp.bmWidth;

	mTextureBuffer = new int *[mTextureHeight];
	for (int i = 0; i < mTextureHeight; i++)
		mTextureBuffer[i] = new int[mTextureWidth];

	SelectObject(hdc, bitmap);
	for (int i = 0; i < mTextureHeight; i++)
	{
		for (int j = 0; j < mTextureWidth; j++)
			mTextureBuffer[i][j] = GetPixel(hdc, i, j);
	}
}

void Device::Sampling(Vertex& vertex) const
{
	if (mTextureBuffer == NULL || IsTextureEnabled( ) == false )
		return;

	Vector2 uv = vertex.mTextureUV;
	float z = 1.0f / vertex.mReciprocalOfZ;
	int x = (int)( uv.x * z * (mTextureWidth - 1) );
	int y = (int)( uv.y * z * (mTextureHeight - 1) );

	y = y >= mTextureHeight ? (mTextureHeight - 1) : y;
	y = y < 0 ? 0 : y;

	x = x >= mTextureWidth ? (mTextureWidth - 1) : x;
	x = x < 0 ? 0 : x;

	int color = mTextureBuffer[y][x];
	//Stream::PrintVector2(vertex.mTextureUV, "uv");
	//Stream::PrintVector2(Vector2(y, x), "UVPosition");
	//Stream::PrintVector4(vertex.mPos, "vertext Position");
	vertex.mColor.r = GetRValue(color);
	vertex.mColor.g = GetGValue(color);
	vertex.mColor.b = GetBValue(color);
	vertex.mColor.a = 1.0f;
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
	if (x >= mWidth || x < 0 || y < 0 || y >= mHeight)
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
			Sampling(vertex);
			DrawPoint(Vector3(vertex.mPos.x, vertex.mPos.y, vertex.mPos.z ) , vertex.mColor);
		}
	}
	else
	{
		const Vertex& down = (ep.y > sp.y) ? start : end;
		const Vertex& up = (ep.y > sp.y) ? end : start;

		for (int i = down.mPos.y; i < up.mPos.y; i++)
		{
			float lerp = (i - down.mPos.y) / (up.mPos.y - down.mPos.y);
			Vertex vertex = Vertex::VertexLerp(down, up, lerp);
			Sampling(vertex);
			DrawPoint(Vector3(vertex.mPos.x, vertex.mPos.y, vertex.mPos.z), vertex.mColor);
		}
	}
}

void Device::DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
{
	Vertex newv1 = v1;
	Vertex newv2 = v2;
	Vertex newv3 = v3;

	ShaderVertex(newv1);
	ShaderVertex(newv2);
	ShaderVertex(newv3);

	mTransform->TransformToViewSpace(newv2.mPos, v2.mPos);
	mTransform->TransformToViewSpace(newv3.mPos, v3.mPos);
	mTransform->TransformToViewSpace(newv1.mPos, v1.mPos);

	if (CheckBackCull(newv1, newv2, newv3))
		return;

	std::vector<Triangle> triangles = FrustumCulling(newv1, newv2, newv3);

	for (int i = 0; i < triangles.size(); i++)
	{
		Triangle triangle = triangles[i];
		Vertex& ver1 = triangle.mVertices[0];
		Vertex& ver2 = triangle.mVertices[1];
		Vertex& ver3 = triangle.mVertices[2];

		mTransform->TransformToProjectSpace(ver1.mPos, ver1.mPos);
		ver1.PrepareTextureUV();
		mTransform->TransformToScreenSpace(ver1.mPos);

		mTransform->TransformToProjectSpace(ver2.mPos, ver2.mPos);
		ver2.PrepareTextureUV();
		mTransform->TransformToScreenSpace(ver2.mPos);

		mTransform->TransformToProjectSpace(ver3.mPos, ver3.mPos);
		ver3.PrepareTextureUV();
		mTransform->TransformToScreenSpace(ver3.mPos);

		if (ver1.mPos.y == ver2.mPos.y && ver1.mPos.y == ver3.mPos.y)
			return;

		DrawLine(ver1, ver2);
		DrawLine(ver3, ver2);
		DrawLine(ver1, ver3);
	}
}

void Device::FillTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
{
	Vertex newv1 = v1;
	Vertex newv2 = v2;
	Vertex newv3 = v3;

	ShaderVertex(newv1);
	ShaderVertex(newv2);
	ShaderVertex(newv3);

	mTransform->TransformToViewSpace(newv1.mPos, v1.mPos);
	mTransform->TransformToViewSpace(newv2.mPos, v2.mPos);
	mTransform->TransformToViewSpace(newv3.mPos, v3.mPos);

	if (CheckBackCull(newv1, newv2, newv3))
		return;

	//newv1.mTextureUV.x = 0.0f;
	//newv1.mTextureUV.y = 1.0f;

	//newv2.mTextureUV.x = 1.0f;
	//newv2.mTextureUV.y = 1.0f;

	//newv3.mTextureUV.x = 1.0f;
	//newv3.mTextureUV.y = 0.0f;

	std::vector<Triangle> triangles = FrustumCulling(newv1, newv2, newv3);

	for (int i = 0; i < triangles.size(); i++)
	{
		Triangle triangle = triangles[i];
		Vertex& ver1 = triangle.mVertices[0];
		Vertex& ver2 = triangle.mVertices[1];
		Vertex& ver3 = triangle.mVertices[2];

		mTransform->TransformToProjectSpace(ver1.mPos, ver1.mPos);
		ver1.PrepareTextureUV();
		mTransform->TransformToScreenSpace(ver1.mPos);

		mTransform->TransformToProjectSpace(ver2.mPos, ver2.mPos);
		ver2.PrepareTextureUV();
		mTransform->TransformToScreenSpace(ver2.mPos);

		mTransform->TransformToProjectSpace(ver3.mPos, ver3.mPos);
		ver3.PrepareTextureUV();
		mTransform->TransformToScreenSpace(ver3.mPos);

		if (ver1.mPos.y == ver2.mPos.y && ver1.mPos.y == ver3.mPos.y)
			return;

		FillTriangleHelper(ver1, ver2, ver3);
	}
}

void SwapVertex(Vertex& v1, Vertex& v2)
{
	Vertex tmp = v1;
	v1 = v2;
	v2 = tmp;
}

std::vector<Vertex> Device::Interpolate(const Vertex& v1, const Vertex& v2) const
{
	std::vector<Vertex> values;
	if (v1.mPos.y == v2.mPos.y)
	{
		values.push_back(v1);
		return values;
	}

	const Vertex& topv = v1.mPos.y < v2.mPos.y ? v1 : v2;
	const Vertex& bottomv = v1.mPos.y > v2.mPos.y ? v1 : v2;

	int y1 = (int)(v1.mPos.y);
	int y2 = (int)(v2.mPos.y);

	int top = min(y1, y2);
	int bottom = max(y1, y2);

	assert(top <= bottom);

	int limittop = max(0, top);
	int limitbottom = min(mHeight - 1, bottom);

	for (int i = limittop; i <= limitbottom; i++)
	{
		Vertex vertex = Vertex::VertexLerp(topv, bottomv, (float)(i - top) / (float)(bottom - top));
		vertex.mPos.y = i;
		values.push_back(vertex);
	}

	return values;
}

void Device::FillTriangleHelper(Vertex v1, Vertex v2, Vertex v3) const
{
	if (v1.mPos.y > v2.mPos.y)
		SwapVertex(v1, v2);

	if (v1.mPos.y > v3.mPos.y)
		SwapVertex(v1, v3);

	if (v2.mPos.y > v3.mPos.y)
		SwapVertex(v2, v3);

	std::vector<Vertex> shortside1 = Interpolate(v1, v2);
	std::vector<Vertex> shortside2 = Interpolate(v2, v3);
	std::vector<Vertex> longsides = Interpolate(v1, v3);

	if (longsides.size() == 0)
		return;

	if (shortside1.size()>=1)
		shortside1.pop_back();
	shortside1.insert(shortside1.end(), shortside2.begin(), shortside2.end());

	if (shortside1.size() != longsides.size())
		return;

	int halfsize = shortside1.size() / 2;
	std::vector<Vertex>& leftp = shortside1.at(halfsize).mPos.x < longsides.at(halfsize).mPos.x ? shortside1 : longsides;
	std::vector<Vertex>& rightp = shortside1.at(halfsize).mPos.x > longsides.at(halfsize).mPos.x ? shortside1 : longsides;
	for (int i = 0; i < leftp.size(); i++)
	{
		Vertex& left = leftp.at(i);
		Vertex& right = rightp.at(i);
		//Stream::PrintVector2(Vector2((int)left.mPos.x, (int)left.mPos.y), "left");
		//Stream::PrintVector2(Vector2((int)right.mPos.x, (int)right.mPos.y), "right");

		for (int j = left.mPos.x; j < right.mPos.x; j++)
		{
			Vertex vertex = Vertex::VertexLerp(left, right, (float)(j - left.mPos.x) / (float)(right.mPos.x - left.mPos.x));
			vertex.mPos.x = j;
			Sampling(vertex);
			DrawPoint(Vector3(vertex.mPos.x, vertex.mPos.y, vertex.mPos.z), vertex.mColor);
		}
	}
}

void Device::DrawQuadrangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) const
{
	DrawTriangle(v1, v2, v3);
	DrawTriangle(v1, v3, v4);
}

void Device::FillQuadrangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) const
{
	FillTriangle(v1, v2, v3);
	FillTriangle(v1, v3, v4);
}

std::vector<Triangle> Device::FrustumCullingHelper(const vector<Triangle>& triangles, const Vector4& plane) const
{
	vector<Triangle> totaltriangle;
	for (int i = 0; i < triangles.size(); i++)
	{
		vector<Triangle> tgs = ClippingPlane::ClipTriangle(triangles[i], mNearPlane);
		for (int i = 0; i < tgs.size(); i++)
			totaltriangle.push_back(tgs[i]);
	}

	return totaltriangle;
}

std::vector<Triangle> Device::FrustumCulling(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
{
	Triangle triangle;
	triangle.mVertices.push_back(v1);
	triangle.mVertices.push_back(v2);
	triangle.mVertices.push_back(v3);

	vector<Triangle> triangles = ClippingPlane::ClipTriangle(triangle, mNearPlane);
	vector<Triangle> triangles1 = FrustumCullingHelper(triangles, mFarPlane);

	return triangles1;
}

bool Device::CheckBackCull(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
{
	if (mBackCull == false) return false;
	Vector4 vec1 = v2.mPos - v1.mPos;
	Vector4 vec2 = v3.mPos - v1.mPos;
	Vector4 normal = Vector4::Cross( vec1, vec2 );

	return normal.z < 0;
}

void Device::ShaderVertex(Vertex& v1) const
{
	if (IsLightingEnabled() == false)
		return;

	Vector3 intensity = LightShader(v1, mDirectionalLight) + LightShader(v1, mPointLight) + LightShader(v1, mAmbientLight);
	v1.mColor = v1.mColor * intensity;

	v1.mColor.r = v1.mColor.r > 255.0f ? 255.0f : v1.mColor.r;
	v1.mColor.g = v1.mColor.g > 255.0f ? 255.0f : v1.mColor.g;
	v1.mColor.b = v1.mColor.b > 255.0f ? 255.0f : v1.mColor.b;
	v1.mColor.a = v1.mColor.a > 255.0f ? 255.0f : v1.mColor.a;
}

Vector3 Device::LightShader(const Vertex& vertex, const Light& light) const
{
	Vector3 intensity;
	if (light.mType == Light::_Light_Ambient)
	{
		intensity = light.mIntensity;
	}
	else
	{
		Vector4 campos(mCamera.mEye.x, mCamera.mEye.y, mCamera.mEye.z, 1.0f);
		Vector3 specular = Light::CalcSpecular(campos, light, vertex);
		Vector3 diffuse = Light::CalcDiffuse(light, vertex);

		intensity = specular + diffuse;
	}

	return intensity;
}

void Device::MoveCameraForwardOrBackward(float dis)
{
	Vector3 forward = (mCamera.mLook - mCamera.mEye).Normorlize();
	mCamera.mEye = mCamera.mEye + forward * dis;
	mCamera.mLook = mCamera.mLook + forward * dis;

	//Stream::PrintVector3(mCamera.mEye, "mCamera.mEye");
	//Stream::PrintVector3(mCamera.mLook, "mCamera.mLook");

	//mCamera.mEye = Vector3(25.4056f, 50.0f, 25.4056f);
	//mCamera.mLook = Vector3(80.4056f, 50.0f, 80.4056f);

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