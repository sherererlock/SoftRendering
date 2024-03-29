
#include<iostream>
#include"Device.h"

Device* device = NULL;

void DrawTriangle()
{
	Vertex v1, v2, v3, v4;
	v1.mPos = Vector4( 100.0f, 0.0f, 0.0f, 1.0f );
	v1.mColor = Color( 255.0f, 0.0f, 0.0f, 1.0f );
	v1.mTextureUV = Vector2(1.0f, 1.0f);

	v2.mPos = Vector4( 0.0f, 0.0f, 100.0f, 1.0f );
	v2.mColor = Color( 0.0f, 255.0f, 0.0f, 1.0f );
	v2.mTextureUV = Vector2(0.0f,1.0f);

	v3.mPos = Vector4( 50.0f, 100.0f, 50.0f, 1.0f );
	v3.mColor = Color(0.0f, 0.0f, 255.0f, 1.0f);
	v3.mTextureUV = Vector2(0.5f, 0.0f);

	Vector4 vec1 = v2.mPos - v1.mPos;
	Vector4 vec2 = v3.mPos - v1.mPos;
	Vector4 normal = Vector4::Cross(vec1, vec2);

	v1.mNormal = v2.mNormal = v3.mNormal = normal.Normalize();

	if (device->IsWireframe())
		device->DrawTriangle(v1, v2, v3);

	if (device->IsWireframe() == false)
		device->FillTriangle(v1, v2, v3);
}

void InitTexture(Vertex &ve, float u, float v)
{
	ve.mTextureUV.x = u;
	ve.mTextureUV.y = v;
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

	InitTexture(v1, 0.0f, 0.0f);
	InitTexture(v2, 1.0f, 0.0f);
	InitTexture(v3, 1.0f, 1.0f);
	InitTexture(v4, 0.0f, 1.0f);
	InitTexture(v5, 0.0f, 0.0f);
	InitTexture(v6, 1.0f, 0.0f);
	InitTexture(v7, 1.0f, 1.0f);
	InitTexture(v8, 0.0f, 1.0f);

	Vector4  plane16, plane27, plane38, plane18, plane13, plane57;
	plane16 = Vector4(0.0f, 0.0f, -1.0f, 1.0f);
	plane27 = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	plane38 = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	plane18 = Vector4(-1.0f, 0.0f, 0.0f, 1.0f);
	plane13 = Vector4(0.0f, -1.0f, 0.0f, 1.0f);
	plane57 = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

	v1.mNormal = plane16 + plane18 + plane13;
	v1.mNormal.Normalize();
	v2.mNormal = plane27 + plane16 + plane13;
	v2.mNormal.Normalize();
	v3.mNormal = plane27 + plane38 + plane13;
	v3.mNormal.Normalize();
	v4.mNormal = plane38 + plane18 + plane13;
	v4.mNormal.Normalize();

	v5.mNormal = plane57 + plane18 + plane13;
	v5.mNormal.Normalize();
	v6.mNormal = plane16 + plane57 + plane27;
	v6.mNormal.Normalize();
	v7.mNormal = plane27 + plane57 + plane18;
	v7.mNormal.Normalize();
	v8.mNormal = plane38 + plane57 + plane18;
	v8.mNormal.Normalize();

	if (device->IsWireframe())
	{
		device->DrawQuadrangle(v2, v1, v4, v3);
		device->DrawQuadrangle(v1, v2, v6, v5);
		device->DrawQuadrangle(v4, v1, v5, v8);
		device->DrawQuadrangle(v2, v3, v7, v6);
		device->DrawQuadrangle(v3, v4, v8, v7);
		device->DrawQuadrangle(v5, v6, v7, v8);
	}

	if (device->IsWireframe() == false)
	{
		device->FillQuadrangle(v2, v1, v4, v3);
		device->FillQuadrangle(v1, v2, v6, v5);
		device->FillQuadrangle(v4, v1, v5, v8);
		device->FillQuadrangle(v2, v3, v7, v6);
		device->FillQuadrangle(v3, v4, v8, v7);
		device->FillQuadrangle(v5, v6, v7, v8);
	}
}

int main()
{
	device = new Device();
	device->Init(800, 600);
	device->EnableTexture(false);
	device->SetDrawObject(1);
	device->EnableLight(true);
	device->LoadImageBuffer("newt.bmp");
	while (true)
	{
		if (device->GetDrawBoard( )->IsKeyDown(VK_ESCAPE))
			break;

		if ( device->GetDrawBoard()->IsKeyDown(87))
		{
			device->MoveCameraForwardOrBackward(0.1f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(83))
		{
			device->MoveCameraForwardOrBackward(-0.1f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(65))
		{
			device->MoveCameraRightOrLeft(-0.1f);
		}
		else if ( device->GetDrawBoard()->IsKeyDown(68))
		{
			device->MoveCameraRightOrLeft(0.1f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(VK_RIGHT))
		{
			device->RotateCameraAroundY(-0.002f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(VK_LEFT))
		{
			device->RotateCameraAroundY(0.002f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(VK_UP))
		{
			device->RotateCameraAroundX(-0.002f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(VK_DOWN))
		{
			device->RotateCameraAroundX(0.002f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(81))
		{
			device->MoveCameraUpOrDown(0.5f);
		}
		else if (device->GetDrawBoard()->IsKeyDown(69))
		{
			device->MoveCameraUpOrDown(-0.5f);
		}
		// Lighting key number 1,2
		else if (device->GetDrawBoard()->IsKeyDown(1 + 48))
		{
			device->EnableLight(true);
		}
		else if (device->GetDrawBoard()->IsKeyDown(2 + 48))
		{
			device->EnableLight(false);
		}
		// Texture key number 3,4
		else if (device->GetDrawBoard()->IsKeyDown(3 + 48))
		{
			if (device->GetDrawObject() == 1)
				device->EnableTexture(true);
		}
		else if (device->GetDrawBoard()->IsKeyDown(4 + 48))
		{
			device->EnableTexture(false);
		}
		// wireframe 5,6
		else if (device->GetDrawBoard()->IsKeyDown(5 + 48))
		{
			device->EnableWireframe(true);
		}
		else if (device->GetDrawBoard()->IsKeyDown(6 + 48))
		{
			device->EnableWireframe(false);
		}
		// Draw Triangle 7
		else if ( device->GetDrawBoard()->IsKeyDown(7+48))
		{
			device->SetDrawObject(1);
		}
		// Draw Cube 8
		else if (device->GetDrawBoard()->IsKeyDown(8 + 48))
		{
			device->EnableTexture(false);
			device->SetDrawObject(2);
		}

		device->ClearBuffer();

		if (device->GetDrawObject( ) == 1)
			DrawTriangle();
		else if (device->GetDrawObject() == 2)
			DrawHexahedron();

		device->GetDrawBoard()->Update();
	}

	device->Close();

	delete device;

	return 0;
}