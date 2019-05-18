
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
	device->DrawTriangle(v1, v2, v3);
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

		DrawTriangle();

		device->GetDrawBoard()->Update();
	}

	device->Close();

	delete device;

	return 0;
}