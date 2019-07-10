#pragma once
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

	DrawBoard* mDrawBoard;
	int** mFrameBuffer;
	float* mZBuffer;

	Transform*	mTransform;
	Camera		mCamera;
	Light		mPoint;
	Light		mSky;
	Light		mAmbient;

public:
	Device() : mWidth(800), mHeight(600), mDrawBoard(NULL), mFrameBuffer(NULL), mWireFrame(false) {}
	Device(int width, int height) :mWidth(width), mHeight(height), mDrawBoard(NULL), mFrameBuffer(NULL), mWireFrame(false) {}
	~Device() { }
	inline DrawBoard* GetDrawBoard() { return mDrawBoard; }
	inline Transform* GetTransform() { return mTransform; }
	inline bool GetWireFrame() { return mWireFrame; }
	inline void SetWireFrame(bool wireframe) { mWireFrame = wireframe; }
	void Init(int w, int h);
	void ClearBuffer();
	void Close();
	void DrawPoint(const Vector3& point, const Color& color);
	void DrawPoint3D(const Vector3& point, const Color& color);
	void DrawLineDDA(const Vertex& start, const Vertex& end);
	void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
	void FillTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
	bool CheckBackCull(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
	void LightShader(Vertex& vertex, const Light& light) const;
};