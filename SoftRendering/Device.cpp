
#include"Device.h"
#include"DrawBoard.h"

void Device::Init(int w, int h)
{
	mWidth = w;
	mHeight = h;
	mDrawBoard = new DrawBoard();
	mDrawBoard->Init(w, h);
	int* fb = (int*)mDrawBoard->GetFramebuffer();
	mFrameBuffer = (int**)malloc(h * sizeof(int*));

	for (int i = 0; i < w; i++)
		mFrameBuffer[i] = fb + i * w;
}

void Device::Close()
{
	if(mDrawBoard!=NULL)
		mDrawBoard->Close();

	if (mFrameBuffer != NULL)
	{
		free(mFrameBuffer);
		mFrameBuffer = NULL;
	}
}

void Device::DrawPoint(const Vertex& point)
{
	int x = point.mPos.x;
	int y = point.mPos.y;
	if (x > mWidth || x < 0 || y < 0 || y > mHeight) return;
	mFrameBuffer[x][y] = (int)point.mColor.r << 16 | (int)point.mColor.g << 8 | (int)point.mColor.b;
}

void Device::DrawLine(const Vertex& start, const Vertex& end)
{

}