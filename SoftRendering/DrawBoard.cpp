
#include"DrawBoard.h"
#include<assert.h> 
#include<iostream>

int KeysDown[512]; // ��¼����״̬

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//������Ϣ
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
	static TCHAR szAppName[] = TEXT("SoftRendering"); //�������ڵ�ʱ����Ҫһ����������
	WNDCLASS wndclass; //�������������
	Close();

	wndclass.style = CS_BYTEALIGNCLIENT;
	wndclass.lpfnWndProc = WndProc;  /*���ｫ�ص����������ָ�ֵ����windows����ص�*/
	wndclass.cbClsExtra = 0;  //���Ӳ�����ͨ�������Ϊ0
	wndclass.cbWndExtra = 0;  //���Ӳ�����ͨ�������Ϊ0
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); /*����ͼ�꣬LoadIcon()�Ǽ���ͼ�꣬�����Ǽ���һ��ϵͳ��Դͼ�꣬LoadIcon()��ԭ����HICON LoadIcon(HINSTANCE, LPCSTR);*/
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  /*������꣬ͬ������*/
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);  /*���ڻ�ˢ��������ʹ�õİ�ɫ��ˢ�����Դ��������Ĵ��ڵı�����ɫ���ǰ�ɫ��*/
	wndclass.lpszMenuName = NULL;  //���ڲ˵����ƣ�����û�в˵�����ΪNULL
	wndclass.lpszClassName = szAppName;  //���������ƣ�������������ƿ���Ϊ������ڵ�Ψһ��ʶ

	assert(RegisterClass(&wndclass));

	mHWnd = CreateWindow(szAppName,    //��������
		TEXT("SoftRendering"),    //���ڱ��⣬���ڴ��ڵ����ϽǱ�������ʾ
		WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, //���ڷ��
		0,  //�������Ͻ�xλ�ã�����ʹ�õ�ϵͳĬ��ֵ�����Զ���
		0,  //�������Ͻ�yλ��
		mWidth,  //���ڵĿ��
		mHeight,  //���ڵĸ߶�
		NULL, //�ô��ڵĸ����ڻ������ߴ��ڵľ���������ò�������ΪNULL
		NULL, //���ڲ˵����������û�в˵�������ΪNULL
		wndclass.hInstance, //���ھ��
		NULL  //���ݸ�����WM_CREATE��Ϣ��һ�����������ﲻ�ã�����ΪNULL
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
