
#include<iostream>
#include"Device.h"

Device* device = NULL;

void DrawTriangle()
{
	Vertex v1, v2, v3;
	v1.mPos = Vector4( 100.0f, 0.0f, 0.0f, 1.0f );
	v1.mColor = Color( 255.0f, 0.0f, 0.0f, 1.0f );
	v2.mPos = Vector4( 0.0f, 0.0f, 100.0f, 1.0f );
	v2.mColor = Color( 0.0f, 255.0f, 0.0f, 1.0f );
	v3.mPos = Vector4( 50.0f, 100.0f, 50.0f, 1.0f );
	v3.mColor = Color(0.0f, 0.0f, 255.0f, 1.0f);

	Vertex v4, v5, v6;
	v4.mPos = Vector4(80.0f, 0.0f, 0.0f, 1.0f);
	v4.mColor = Color(0.0f, 255.0f, 0.0f, 1.0f);
	v5.mPos = Vector4(0.0f, 0.0f, 80.0f, 1.0f);
	v5.mColor = Color(0.0f, 0.0f, 255.0f, 1.0f);
	v6.mPos = Vector4(50.0f, 100.0f, 50.0f, 1.0f);
	v6.mColor = Color(0.0f, 0.0f, 255.0f, 1.0f);

	//v1.mPos = Vector4( 50.0f, 0.0f, 50.0f, 1.0f );
	//v1.mColor = Color( 255.0f, 0.0f, 0.0f, 1.0f );
	//v2.mPos = Vector4(100.0f, 0.0f, 50.0f, 1.0f);
	//v2.mColor = Color( 0.0f, 255.0f, 0.0f, 1.0f );
	//v3.mPos = Vector4( 100.0f, 0.0f, 100.0f, 1.0f);
	//v3.mColor = Color(0.0f, 0.0f, 255.0f, 1.0f);

	//device->DrawTriangle(v1, v2, v3);
	device->FillTriangle(v1, v2, v3);
	//device->FillTriangle(v4, v5, v6);
}

void DrawHexahedron()
{
	Vertex v1, v2, v3, v4, v5, v6, v7, v8;
	v1.mPos = { 50.0f, 0.0f, 50.0f, 1.0f };
	v2.mPos = { 100.0f, 0.0f, 50.0f, 1.0f };
	v3.mPos = { 100.0f, 0.0f, 100.0f, 1.0f };
	v4.mPos = { 50.0f, 0.0f, 100.0f, 1.0f };
	v5.mPos = { 50.0f, 50.0f, 50.0f, 1.0f };
	v6.mPos = { 100.0f, 50.0f, 50.0f, 1.0f };
	v7.mPos = { 100.0f, 50.0f, 100.0f, 1.0f };
	v8.mPos = { 50.0f, 50.0f, 100.0f, 1.0f };

	v1.mColor = Color(255.0f, 0.0f, 0.0f, 1.0f);
	v2.mColor = Color(0.0f, 255.0f, 0.0f, 1.0f);
	v3.mColor = Color(0.0f, 0.0f, 255.0f, 1.0f);
	v4.mColor = Color(0.0f, 0.0f, 255.0f, 1.0f);
	v5.mColor = Color(0.0f, 255.0f, 0.0f, 1.0f);
	v6.mColor = Color(255.0f, 255.0f, 0.0f, 1.0f);
	v7.mColor = Color(0.0f, 255.0f, 255.0f, 1.0f);
	v8.mColor = Color(255.0f, 0.0f, 255.0f, 1.0f);

	//device->DrawQuadrangle(v2, v1, v4, v3);
	//device->DrawQuadrangle(v1, v2, v6, v5);
	//device->DrawQuadrangle(v4, v1, v5, v8);
	device->DrawQuadrangle(v2, v3, v7, v6);
	//device->DrawQuadrangle(v3, v4, v8, v7);
	//device->DrawQuadrangle(v5, v6, v7, v8);

	device->FillQuadrangle(v2, v1, v4, v3);
	device->FillQuadrangle(v1, v2, v6, v5);
	device->FillQuadrangle(v4, v1, v5, v8);
	device->FillQuadrangle(v2, v3, v7, v6);
	device->FillQuadrangle(v3, v4, v8, v7);
	device->FillQuadrangle(v5, v6, v7, v8);
}

int main()
{
	device = new Device();
	device->Init(800, 600);
	Vertex startp;
	startp.mColor = Color(255.0f, 0.0f, 0.0f, 255.0f);
	Vertex endp;
	endp.mColor = Color(0.f, 0.f, 0.f, 255);

	float y = 450.5f;
	while (true)
	{
		if (device->GetDrawBoard( )->IsKeyDown(VK_ESCAPE))
			break;

		if (device->GetDrawBoard()->IsKeyDown(VK_UP) || device->GetDrawBoard()->IsKeyDown(87))
		{
			device->MoveCameraForwardOrBackward(1.0f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(VK_DOWN) || device->GetDrawBoard()->IsKeyDown(83))
		{
			device->MoveCameraForwardOrBackward(-1.0f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(VK_LEFT) || device->GetDrawBoard()->IsKeyDown(65))
		{
			device->MoveCameraRightOrLeft(-1.0f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(VK_RIGHT) || device->GetDrawBoard()->IsKeyDown(68))
		{
			device->MoveCameraRightOrLeft(1.0f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(81))
		{
			device->MoveCameraUpOrDown(1.0f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(69))
		{
			device->MoveCameraUpOrDown(-1.0f);
		}

		device->ClearBuffer();

		//DrawTriangle();
		DrawHexahedron();

		device->GetDrawBoard()->Update();
	}

	device->Close();

	delete device;

	return 0;
}