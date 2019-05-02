
#include<iostream>
#include"Device.h"

int main()
{
	Device* device = new Device();
	device->Init(800, 600);
	Vertex startp;
	startp.mColor = Color(255.0f, 0.0f, 0.0f, 255.0f);
	Vertex endp;
	endp.mColor = Color(0.f, 0.f, 0.f, 255);

	float y = 450.5f;
	while (true)
	{
		//for (int i =0; i< 100; i ++)
		//	device->DrawPoint(Vector3(102.5f, i, 0), Color(255, 0, 0, 1));

		if (device->GetDrawBoard( )->IsKeyDown(VK_ESCAPE))
			break;

		device->ClearBuffer();

		//device->DrawLineDDA(startp, endp);

		startp.mPos = Vector3(350.0f, 350.0f, 0);
		endp.mPos = Vector3(450.5f, y, 0);
		device->DrawLineDDA(startp, endp);
		if (y > 0.0f)
			y -= 0.5f;

		device->GetDrawBoard()->Update();
	}

	device->Close();

	delete device;

	return 0;
}