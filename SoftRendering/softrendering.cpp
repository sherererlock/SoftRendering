
#include<iostream>
#include"Device.h"

Device* device = NULL;

void DrawTriangle()
{
	Vertex v1, v2, v3;
	//v1.mPos = Vector4( 100.0f, 0.0f, 0.0f, 1.0f );
	//v1.mColor = Color( 255.0f, 0.0f, 0.0f, 1.0f );
	//v2.mPos = Vector4( 0.0f, 0.0f, 100.0f, 1.0f );
	//v2.mColor = Color( 0.0f, 255.0f, 0.0f, 1.0f );
	//v3.mPos = Vector4( 50.0f, 100.0f, 50.0f, 1.0f );
	//v3.mColor = Color(0.0f, 0.0f, 255.0f, 1.0f);

	v1.mPos = Vector4( 50.0f, 0.0f, 50.0f, 1.0f );
	v1.mColor = Color( 255.0f, 0.0f, 0.0f, 1.0f );
	v2.mPos = Vector4(100.0f, 0.0f, 50.0f, 1.0f);
	v2.mColor = Color( 0.0f, 255.0f, 0.0f, 1.0f );
	v3.mPos = Vector4( 100.0f, 0.0f, 100.0f, 1.0f);
	v3.mColor = Color(0.0f, 0.0f, 255.0f, 1.0f);

	device->DrawTriangle(v1, v2, v3);
	device->FillTriangle(v1, v2, v3);
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
	//device->DrawQuadrangle(v2, v3, v7, v6);
	//device->DrawQuadrangle(v3, v4, v8, v7);
	//device->DrawQuadrangle(v5, v6, v7, v8);

	device->FillQuadrangle(v2, v1, v4, v3);
	//device->FillQuadrangle(v1, v2, v6, v5);
	//device->FillQuadrangle(v4, v1, v5, v8);
	//device->FillQuadrangle(v2, v3, v7, v6);
	//device->FillQuadrangle(v3, v4, v8, v7);
	//device->FillQuadrangle(v5, v6, v7, v8);
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

		device->ClearBuffer();

		//DrawTriangle();
		DrawHexahedron();

		device->GetDrawBoard()->Update();
	}

	device->Close();

	delete device;

	return 0;
}