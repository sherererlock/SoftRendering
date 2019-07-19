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
	static vector<Vertex> ClipTriangle(const vector<Vertex>& vertexs, const Vector4& plane);
};

vector<Vertex>  ClippingPlane::ClipTriangle(const vector<Vertex>& vertexs, const Vector4& plane)
{
	vector<Vertex> frontp;
	vector<Vertex> behindp;
	for (int i = 0; i < vertexs.size(); i++)
	{
		Vertex& vertex = vertexs.at[i];
		float distance = Vector4::Dot(plane, vertex.mPos) + plane.w;
		if (distance > 0)
			frontp.push_back(vertex);
		else
			behindp.push_back(vertex);
	}

	if (behindp.size() == 0)
		return vertexs;

	if (frontp.size() == 0)
		return frontp;

	vector<Vertex> triangle;
	if (frontp.size() == 1)
	{
		for (int i = 0; i < behindp.size(); i ++)
		{ 
			float lerp = (-plane.z - Vector4::Dot(plane, frontp.at[0]) /
				Vector4::Dot(plane, behindp.at[i] - frontp.at[0]));

			triangle.push_back(Vertex::VertexLerp(frontp.at[0], behindp.at[0], lerp));
		}
	}
	else
	{
		for (int i = frontp.size() - 1; i >= 0 ; i--)
		{
			float lerp = (-plane.z - Vector4::Dot(plane, frontp.at[i]) /
				Vector4::Dot(plane, behindp.at[0] - frontp.at[i]));

			triangle.push_back(Vertex::VertexLerp(frontp.at[i], behindp.at[0], lerp));
		}
	}

	assert(triangle.size() >= 3);
	return triangle;
}
