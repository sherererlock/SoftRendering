#pragma once

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
	#if 0
		for (int i = 0; i < 4; i ++)
		{
			for(int j = 0; j < 4; j ++)
				mat[i][j] = mat1[i][0] * mat2[0][j] + mat1[i][1] * mat2[1][j] + mat1[i][2] * mat2[2][j] +
				mat1[i][3] * mat2[3][j]
		}
	#else
		// A restric qualified pointer (or reference) is basically a promise
		// to the compiler that for the scope of the pointer, the target of the
		// pointer will only be accessed through that pointer (and pointers
		// copied from it.
		const float* __restrict ap = &mat1.mMat[0][0];
		const float* __restrict bp = &mat2.mMat[0][0];
		float* __restrict cp = &mat.mMat[0][0];

		float a0, a1, a2, a3;

		a0 = ap[0];
		a1 = ap[1];
		a2 = ap[2];
		a3 = ap[3];

		cp[0] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
		cp[1] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
		cp[2] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
		cp[3] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

		a0 = ap[4];
		a1 = ap[5];
		a2 = ap[6];
		a3 = ap[7];

		cp[4] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
		cp[5] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
		cp[6] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
		cp[7] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

		a0 = ap[8];
		a1 = ap[9];
		a2 = ap[10];
		a3 = ap[11];

		cp[8] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
		cp[9] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
		cp[10] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
		cp[11] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

		a0 = ap[12];
		a1 = ap[13];
		a2 = ap[14];
		a3 = ap[15];

		cp[12] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
		cp[13] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
		cp[14] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
		cp[15] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

	#endif
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
};