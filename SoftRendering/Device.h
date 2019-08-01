#pragma once
#include<vector>
#include"DrawBoard.h"
#include"Vector.h"
#include"Color.h"
#include"Vertex.h"
#include"Light.h"
#include"Transform.h"

class Device
{
private:
	int mWidth;
	int mHeight;
	bool mWireFrame;
	bool mBackCull;

	DrawBoard* mDrawBoard;
	int** mFrameBuffer;
	float* mZBuffer;
	int** mTextureBuffer;
	int	mTextureWidth;
	int mTextureHeight;

	Transform*	mTransform;
	Camera		mCamera;
	Light		mPointLight;
	Light		mDirectionalLight;
	Light		mAmbientLight;

	Vector4		mNearPlane;
	Vector4		mFarPlane;
	Vector4		mLeftPlane;
	Vector4		mRightPlane;
	Vector4		mTopPlane;
	Vector4		mBottomPlane;
private:
	std::vector<Triangle> FrustumCullingHelper(const std::vector<Triangle>& triangles, const Vector4& plane) const;

public:
	Device() : mWidth(800), mHeight(600), mDrawBoard(NULL), mFrameBuffer(NULL), mWireFrame(false), mBackCull(false) {}
	Device(int width, int height) :mWidth(width), mHeight(height), mDrawBoard(NULL), mFrameBuffer(NULL), mWireFrame(false) {}
	~Device() { }
	inline DrawBoard* GetDrawBoard() { return mDrawBoard; }
	inline Transform* GetTransform() { return mTransform; }
	inline bool GetWireFrame() { return mWireFrame; }
	inline void SetWireFrame(bool wireframe) { mWireFrame = wireframe; }
	void Init(int w, int h);
	void InitPlane();
	void InitLight();
	void LoadImageBuffer(std::string resname);
	void ClearBuffer();
	void Close();
	void DrawPoint(const Vector3& point, const Color& color) const;
	void DrawPoint3D(const Vector3& point, const Color& color) const;
	void DrawLine(const Vertex& start, const Vertex& end) const;
	void DrawLineDDA(const Vertex& start, const Vertex& end) const;
	void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
	void FillTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
	void FillTriangleHelper(Vertex& v1, Vertex& v2, Vertex& v3) const;
	void FillTriangleHelper1(Vertex& v1, Vertex& v2, Vertex& v3) const;
	void DrawQuadrangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) const;
	void FillQuadrangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) const;
	std::vector<Triangle> FrustumCulling(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
	bool CheckBackCull(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
	void ShaderVertex(Vertex& v1) const;
	Vector3 LightShader(const Vertex& vertex, const Light& light) const;

	void MoveCameraForwardOrBackward(float dis);
	void MoveCameraRightOrLeft(float dis);
	void MoveCameraUpOrDown(float dis);
};