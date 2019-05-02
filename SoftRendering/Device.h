#pragma once
#include"DrawBoard.h"
#include"Vector.h"
#include"Color.h"
#include"Vertex.h"

class Device
{
private:
	int mWidth;
	int mHeight;

	DrawBoard* mDrawBoard;
	int** mFrameBuffer;

public:
	Device() : mWidth(800), mHeight(600), mDrawBoard(NULL), mFrameBuffer(NULL){}
	Device(int width, int height) :mWidth(width), mHeight(height), mDrawBoard(NULL), mFrameBuffer(NULL) {}
	~Device() { }
	inline DrawBoard* GetDrawBoard() { return mDrawBoard; }
	void Init(int w, int h);
	void ClearBuffer();
	void Close();
	void DrawPoint(const Vector3& point, const Color& color);
	void DrawLineDDA(const Vertex& start, const Vertex& end);
};