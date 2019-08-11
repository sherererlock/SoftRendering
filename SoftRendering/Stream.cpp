
#include"Stream.h"

void Stream::PrintInfo(std::string tag)
{
	std::cout << tag.c_str() << std::endl;
}

void Stream::PrintVector2(const Vector2& v, std::string tag)
{
	std::cout << tag.c_str() << " ( " << v.x << ", " << v.y <<" )" << std::endl;
}

void Stream::PrintVector3(const Vector3& v, std::string tag)
{
	std::cout << tag.c_str() << " ( " << v.x << ", " << v.y << ", " << v.z << " )" << std::endl;
}

void Stream::PrintVector4(const Vector4& v, std::string tag)
{
	std::cout << tag.c_str() << " ( " << v.x << ", " << v.y << ", " << v.z << "," << v.w << " )" << std::endl;
}

void Stream::PrintMatrix4D(const Matrix4D& mat, std::string tag)
{
	std::cout << tag.c_str() << std::endl;

	std::cout << "(";
	std::cout << mat.mMat[0][0] << "," << mat.mMat[0][1] << "," << mat.mMat[0][2] << "," << mat.mMat[0][3] << "," << std::endl;
	std::cout << mat.mMat[1][0] << "," << mat.mMat[1][1] << "," << mat.mMat[1][2] << "," << mat.mMat[1][3] << "," << std::endl;
	std::cout << mat.mMat[2][0] << "," << mat.mMat[2][1] << "," << mat.mMat[2][2] << "," << mat.mMat[2][3] << "," << std::endl;
	std::cout << mat.mMat[3][0] << "," << mat.mMat[3][1] << "," << mat.mMat[3][2] << "," << mat.mMat[3][3] << "," << std::endl;
	std::cout << ")" << std::endl;

}