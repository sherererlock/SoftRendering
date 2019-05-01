
#include<iostream>
#include"Device.h"

int main()
{
	Device* device = new Device();
	device->Init(800, 600);

	while (true)
	{
		device->DrawPoint(Vector2(100, 100), Color(255, 255, 255, 255));
		device->GetDrawBoard()->Update();
	}
	return 0;
}