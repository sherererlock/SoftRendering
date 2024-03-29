#pragma once
#include<vector>
#include"DrawBoard.h"
#include"Vector.h"
#include"Color.h"
#include"Vertex.h"
#include"Light.h"
#include"Transform.h"

#define _GET_ALPHA( c ) ( ( (c) & 0xFF000000 ) >> 24 )

#define _GET_RED( c ) ( ( (c) & 0x00FF0000 ) >> 16 )

#define _GET_GREEN( c ) ( ( (c) & 0x0000FF00 ) >> 8 )

#define _GET_BLUE( c ) ( (c) & 0x000000FF )

#define _SET_ALPHA( c, a ) ( (c) = ( (c) & 0x00FFFFFF ) | (a) << 24 )

#define _SET_RED( c, r ) ( (c) = ( (c) & 0xFF00FFFF ) | (r) << 16 )

#define _SET_GREEN( c, g ) ( (c) = ( (c) & 0xFFFF00FF ) | (g) << 8 )

#define _SET_BLUE( c, b ) ( (c) = ( (c) & 0xFFFFFF00 ) | (b) )

#define _COMBINE_COLOR( a, r, g, b ) ( (a) << 24 | (r) << 16 | (g) << 8 | (b) )

#define Round(x) (int((x)+0.5f))
#define PI 3.1415926

class Device
{
public:
	enum mode
	{
		_Lighting	= 0x00000001,
		_Texture	= 0x00000002,
		_Wireframe	= 0x00000004,
	};

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

	int			mDrawMode;

	// 1 ==> triangle
	// 2 ==> cube
	int			mDrawObject;

private:
	std::vector<Triangle> FrustumCullingHelper(const std::vector<Triangle>& triangles, const Vector4& plane) const;

public:
	Device() : mWidth(800), mHeight(600), mDrawBoard(NULL), mFrameBuffer(NULL), mTextureBuffer(NULL), mWireFrame(false), mBackCull(false), mDrawMode(0) {}
	Device(int width, int height) :mWidth(width), mHeight(height), mDrawBoard(NULL), mFrameBuffer(NULL), mTextureBuffer(NULL), mWireFrame(false) {}
	~Device() { }
	inline DrawBoard* GetDrawBoard() { return mDrawBoard; }
	inline Transform* GetTransform() { return mTransform; }
	inline bool GetWireFrame() { return mWireFrame; }
	inline void SetWireFrame(bool wireframe) { mWireFrame = wireframe; }

	inline bool IsLightingEnabled() const
		{ return (mDrawMode & _Lighting) != 0; }
	inline void EnableLight(bool enable)
		{ mDrawMode = enable ? (mDrawMode | _Lighting) : (mDrawMode & ~_Lighting); }

	inline bool IsTextureEnabled() const
		{ return (mDrawMode & _Texture) != 0; }
	inline void EnableTexture(bool enable)
		{ mDrawMode = enable ? (mDrawMode | _Texture) : (mDrawMode & ~_Texture); }

	inline bool IsWireframe() const
	{
		return (mDrawMode & _Wireframe) != 0;
	}
	inline void EnableWireframe(bool enable)
	{
		mDrawMode = enable ? (mDrawMode | _Wireframe) : (mDrawMode & ~_Wireframe);
	}

	inline int GetDrawObject()
		{ return mDrawObject; }
	inline void SetDrawObject(int drawobject)
		{ mDrawObject = drawobject; }

	void Init(int w, int h);
	void InitPlane();
	void InitLight();
	void LoadImageBuffer(std::string resname);
	void DrawImageBuffer() const;
	void Sampling(Vertex& vertex) const;
	void ClearBuffer();
	void Close();
	void DrawPoint(const Vector3& point, const Color& color) const;
	void DrawLine(const Vertex& start, const Vertex& end) const;
	std::vector<Vertex> Interpolate(const Vertex& v1, const Vertex& v2) const;
	void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
	void FillTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
	void FillTriangleHelper(Vertex v1, Vertex v2, Vertex v3) const;
	void DrawQuadrangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) const;
	void FillQuadrangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4) const;
	std::vector<Triangle> FrustumCulling(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
	bool CheckBackCull(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
	void ShaderVertex(Vertex& v1) const;
	Vector3 LightShader(const Vertex& vertex, const Light& light) const;

	void MoveCameraForwardOrBackward(float dis);
	void MoveCameraRightOrLeft(float dis);
	void MoveCameraUpOrDown(float dis);
	void RotateCamera(const Matrix4D& mat);
	void RotateCameraAroundY(float radian);
	void RotateCameraAroundX(float radian);
	void RotateCameraAround(const Vector3& vec, float radian);
};