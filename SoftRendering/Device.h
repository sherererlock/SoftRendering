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
	~Device() { delete mDrawBoard; }
	inline DrawBoard* GetDrawBoard() { return mDrawBoard; }
	void Init(int w, int h);
	void Close();
	void DrawPoint(const Vertex& point);
	void DrawLine(const Vertex& start, const Vertex& end);
};