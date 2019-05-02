#pragma once

#include <windows.h>

class DrawBoard
{
private:
	int		mWidth;
	int		mHeight;

	HWND		mHWnd;
	HDC			mCompatibleDC;
	HBITMAP		mBitMap;
	HBITMAP		mOldBitMap;
	LPVOID		mFrameBuffer;

public:
	DrawBoard():
		mHWnd(NULL), mCompatibleDC(NULL), mBitMap(NULL), mOldBitMap(NULL), mWidth(800),mHeight(600){}
	DrawBoard(int w, int h):
		mHWnd(NULL), mCompatibleDC(NULL), mBitMap(NULL), mOldBitMap(NULL), mWidth(w), mHeight(h) {}
	~DrawBoard() {}
	bool IsKeyDown(int key);
	inline LPVOID GetFramebuffer() { return mFrameBuffer; }
	void Init(int w, int h);
	void Dispatch();
	void Update();
	void Close();
};