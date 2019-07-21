#pragma once
#include "Vector.h"
#include "Vertex.h"
#include<vector>

using namespace std;
// plane formula
// Ax + By + Cz + D = 0
// if exists P(x, y, z)
// < N, P > + D  means the sign distance from p to the plane
// -D is the signed distance form origin to the plane
// plane normal formula 
// N(A, B, C)

class ClippingPlane
{
public:
	static vector<Triangle> ClipTriangle(const Triangle& triangle, const Vector4& plane);
};

vector<Triangle>  ClippingPlane::ClipTriangle(const Triangle& triangle, const Vector4& plane)
{
	vector<Vertex> frontp;
	vector<Vertex> behindp;
	vector<Triangle> triangles;
	for (int i = 0; i < triangle.mVertices.size(); i++)
	{
		Vertex vertex = triangle.mVertices[i];
		float distance = Vector4::Dot(plane, vertex.mPos) + plane.w;
		if (distance > 0)
			frontp.push_back(vertex);
		else
			behindp.push_back(vertex);
	}

	if (behindp.size() == 0)
	{
		triangles.push_back(triangle);
		return triangles;
	}

	if (frontp.size() == 0)
		return triangles;

	vector<Vertex> vertices;
	if (frontp.size() == 1)
	{
		vertices.push_back(frontp[0]);
		for (int i = 0; i < behindp.size(); i ++)
		{ 
			float lerp = (-plane.z - Vector4::Dot(plane, frontp[0].mPos) /
				Vector4::Dot(plane, behindp[i].mPos - frontp[0].mPos));

			vertices.push_back(Vertex::VertexLerp(frontp[0], behindp[0], lerp));
		}
	}
	else
	{
		vertices.push_back(frontp[0]);
		vertices.push_back(frontp[1]);
		for (int i = frontp.size() - 1; i >= 0 ; i--)
		{
			float lerp = (-plane.z - Vector4::Dot(plane, frontp[i].mPos) /
				Vector4::Dot(plane, behindp[0].mPos - frontp[i].mPos));

			vertices.push_back(Vertex::VertexLerp(frontp[i], behindp[0], lerp));
		}
	}

	assert(vertices.size() >= 3);

	for (int i = 0; i + 3 <= vertices.size(); i++)
	{
		Triangle triangle;
		triangle.mVertices.push_back(vertices[i]);
		triangle.mVertices.push_back(vertices[i+1]);
		triangle.mVertices.push_back(vertices[i+2]);

		triangles.push_back(triangle);
	}

	return triangles;
}
