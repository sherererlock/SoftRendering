#pragma once
#include"Vector.h"

class Matrix3D
{
public:
	float mMat[3][3] = 
	{
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }
	};

	Matrix3D( ) { }

	Matrix3D( float a, float b, float c, float d, float e, float f, float g, float h, float i )
	{
		mMat[0][0] = a;
		mMat[0][1] = b;
		mMat[0][2] = c;
		mMat[1][0] = d;
		mMat[1][1] = e;
		mMat[1][2] = f;
		mMat[2][0] = g;
		mMat[2][1] = h;
		mMat[2][2] = i;
	}

	inline const float* operator [ ] ( int i ) const { return mMat[i]; }
	inline float* operator [ ] ( int i ) { return mMat[i]; }

	Matrix3D operator * ( const Matrix3D& v ) const
	{
		Matrix3D tmp;
		Multiply( *this, v, tmp );

		return tmp;
	}

	static void Multiply(const Matrix3D& mat1, const Matrix3D& mat2, Matrix3D& mat)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				mat[i][j] = mat1[i][0] * mat2[0][j] + mat1[i][1] * mat2[1][j] + mat1[i][2] * mat2[2][j];
		}
	}

	Matrix3D transpose() const
	{
	#if 0

	Matrix3D t;
	for ( int i = 0; i < 3; i++ )
		for ( int j = 0; j < 3; j ++ )
			t[i][j] = mMat[j][i];

	return t;

	#else

	return Matrix3D(
		mMat[0][0], mMat[1][0], mMat[2][0],
		mMat[0][1], mMat[1][1], mMat[2][1],
		mMat[0][2], mMat[1][2], mMat[2][2]
	);

	#endif
	}

	Matrix3D& transpose()
	{
		Matrix3D tmp(
			mMat[0][0], mMat[1][0], mMat[2][0],
			mMat[0][1], mMat[1][1], mMat[2][1],
			mMat[0][2], mMat[1][2], mMat[2][2]
		);

		*this = tmp;

		return *this;
	}

	inline Matrix3D& SetIdentity( )
	{
		mMat[0][0] = mMat[1][1] = mMat[2][2] = 1.0F;
		mMat[0][1] = mMat[0][2] = mMat[1][0] = mMat[1][2] = mMat[2][0] = mMat[2][1] = 0.0F;

		return (*this);
	}
};

class Matrix4D
{
public:
	float mMat[4][4] =
	{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	};

	Matrix4D( ) { }

	Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h,
		float i, float j, float k, float l, float m, float n, float o, float p)
	{
		mMat[0][0] = a;
		mMat[0][1] = b;
		mMat[0][2] = c;
		mMat[0][3] = d;
		mMat[1][0] = e;
		mMat[1][1] = f;
		mMat[1][2] = g;
		mMat[1][3] = h;
		mMat[2][0] = i;
		mMat[2][1] = j;
		mMat[2][2] = k;
		mMat[2][3] = l;
		mMat[3][0] = m;
		mMat[3][1] = n;
		mMat[3][2] = o;
		mMat[3][3] = p;
	}

	inline const float* operator [] (int i) const { return mMat[i]; }
	inline float* operator [] (int i) { return mMat[i]; }

	// Multiply the current matrix with another matrix (rhs)
	Matrix4D operator * (const Matrix4D& v) const
	{
		Matrix4D tmp;
		Multiply(*this, v, tmp);

		return tmp;
	}

	static void Multiply(const Matrix4D& mat1, const Matrix4D& mat2, Matrix4D& mat)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				mat[i][j] = mat1[i][0] * mat2[0][j] + mat1[i][1] * mat2[1][j] + mat1[i][2] * mat2[2][j] +
				mat1[i][3] * mat2[3][j];
		}
	}

	Matrix4D transpose() const
	{
#if 0
		Matrix4D t;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				t[i][j] = mMat[j][i];

		return t;
#else
		return Matrix4D(
			mMat[0][0],	mMat[1][0],	mMat[2][0],	mMat[3][0],
			mMat[0][1],	mMat[1][1],	mMat[2][1],	mMat[3][1],
			mMat[0][2],	mMat[1][2],	mMat[2][2],	mMat[3][2],
			mMat[0][3],	mMat[1][3],	mMat[2][3],	mMat[3][3]
		);
#endif
	}

	Matrix4D& transpose()
	{
		Matrix4D tmp(
			mMat[0][0], mMat[1][0], mMat[2][0], mMat[3][0],
			mMat[0][1], mMat[1][1], mMat[2][1], mMat[3][1],
			mMat[0][2], mMat[1][2], mMat[2][2], mMat[3][2],
			mMat[0][3], mMat[1][3], mMat[2][3], mMat[3][3]
		);

		*this = tmp;

		return *this;
	}

	inline Matrix4D& SetIdentity()
	{
		mMat[0][0] = mMat[1][1] = mMat[2][2] = mMat[3][3] = 1.0F;
		mMat[1][0] = mMat[2][0] = mMat[3][0] = mMat[0][1] = mMat[2][1] = mMat[3][1] = 
		mMat[0][2] = mMat[1][2] = mMat[3][2] = mMat[0][3] = mMat[1][3] = mMat[2][3] = 0.0F;

		return (*this);
	}

	static void VectorMul(Vector4& vout, const Vector4& v, const Matrix4D& m)
	{
		vout = (Vector4(m.mMat[0][0] * v.x + m.mMat[1][0] * v.y + m.mMat[2][0] * v.z + m.mMat[3][0] * v.w,
			m.mMat[0][1] * v.x + m.mMat[1][1] * v.y + m.mMat[2][1] * v.z + m.mMat[3][1] * v.w,
			m.mMat[0][2] * v.x + m.mMat[1][2] * v.y + m.mMat[2][2] * v.z + m.mMat[3][2] * v.w,
			m.mMat[0][3] * v.x + m.mMat[1][3] * v.y + m.mMat[2][3] * v.z + m.mMat[3][3] * v.w));
	}
};