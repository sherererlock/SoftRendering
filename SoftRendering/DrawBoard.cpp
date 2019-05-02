
#include"DrawBoard.h"
#include<assert.h> 
#include<iostream>

int KeysDown[512]; // 记录键盘状态

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//处理消息
	switch (msg)
	{
		case WM_CLOSE: KeysDown[27 & 511] = 1; break;
		case WM_KEYDOWN:KeysDown[wparam & 511] = 1; break;
		case WM_KEYUP:KeysDown[wparam & 511] = 0; break;
		default:return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}

void DrawBoard::Init(int w, int h)
{
	mWidth = w;
	mHeight = h;
	static TCHAR szAppName[] = TEXT("SoftRendering"); //创建窗口的时候需要一个窗口类名
	WNDCLASS wndclass; //创建窗口类对象
	Close();

	wndclass.style = CS_BYTEALIGNCLIENT;
	wndclass.lpfnWndProc = WndProc;  /*这里将回到函数的名字赋值用以windows后面回调*/
	wndclass.cbClsExtra = 0;  //附加参数，通常情况下为0
	wndclass.cbWndExtra = 0;  //附加参数，通常情况下为0
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); /*窗口图标，LoadIcon()是加载图标，这里是加载一个系统资源图标，LoadIcon()的原型是HICON LoadIcon(HINSTANCE, LPCSTR);*/
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  /*加载鼠标，同上相似*/
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);  /*窗口画刷，这里是使用的白色画刷，所以创建出来的窗口的背景颜色则是白色的*/
	wndclass.lpszMenuName = NULL;  //窗口菜单名称，这里没有菜单，设为NULL
	wndclass.lpszClassName = szAppName;  //窗口类名称，这个窗口类名称可作为这个窗口的唯一标识

	assert(RegisterClass(&wndclass));

	mHWnd = CreateWindow(szAppName,    //窗口类名
		TEXT("SoftRendering"),    //窗口标题，会在窗口的左上角标题栏显示
		WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, //窗口风格
		0,  //窗口左上角x位置，这里使用的系统默认值，可自定义
		0,  //窗口左上角y位置
		mWidth,  //窗口的宽度
		mHeight,  //窗口的高度
		NULL, //该窗口的父窗口或所有者窗口的句柄，这里用不到，设为NULL
		NULL, //窗口菜单句柄，这里没有菜单，设置为NULL
		wndclass.hInstance, //窗口句柄
		NULL  //传递给窗口WM_CREATE消息的一个参数，这里不用，设置为NULL
	);

	assert(mHWnd);

	BITMAPINFO bitmap = { { sizeof(BITMAPINFOHEADER), mWidth, mHeight, 1, 32, BI_RGB,
		mWidth * mHeight * 4, 0, 0, 0, 0 } };
	RECT rect = { 0, 0, w, h };

	HDC hDC = GetDC(mHWnd);
	mCompatibleDC = CreateCompatibleDC(hDC);
	ReleaseDC(mHWnd, hDC);
	mBitMap = CreateDIBSection(mCompatibleDC, &bitmap, DIB_RGB_COLORS, &mFrameBuffer, 0, 0);
	assert(mBitMap);
	mOldBitMap = (HBITMAP)SelectObject(mCompatibleDC, mBitMap);

	AdjustWindowRect(&rect, GetWindowLong(mHWnd, GWL_STYLE), 0);

	int wx = rect.right - rect.left;
	int wy = rect.bottom - rect.top;
	int sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	int sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) sy = 0;
	SetWindowPos(mHWnd, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));

	SetForegroundWindow(mHWnd);
	ShowWindow(mHWnd, SW_NORMAL);
	Dispatch();

	memset(mFrameBuffer, 0, mWidth * mHeight * 4);
	memset(KeysDown, 0, sizeof(int) * 512);
}

void DrawBoard::Dispatch()
{
	MSG msg;
	while (1) 
	{
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
		if (!GetMessage(&msg, NULL, 0, 0)) break;
		DispatchMessage(&msg);
	}
}

void DrawBoard::Update()
{
	HDC dc = GetDC(mHWnd);
	BitBlt(dc, 0, 0, mWidth, mHeight, mCompatibleDC, 0, 0, SRCCOPY);
	ReleaseDC(mHWnd, dc);
	Dispatch();
}

void DrawBoard::Close()
{
	if (mCompatibleDC != NULL)
	{
		if (mOldBitMap)
			SelectObject(mCompatibleDC, mOldBitMap);

		mOldBitMap = NULL;
		DeleteDC(mCompatibleDC);
		mCompatibleDC = NULL;
	}

	if (mBitMap != NULL)
	{
		DeleteObject(mBitMap);
		mBitMap = NULL;
	}

	if (mHWnd!=NULL)
	{
		CloseWindow(mHWnd);
		mHWnd = NULL;
	}
}

bool DrawBoard::IsKeyDown(int key)
{
	//std::cout << key<<"_"<<KeysDown[key & 511]<<"\n";
	return KeysDown[key & 511]== 1;
}
