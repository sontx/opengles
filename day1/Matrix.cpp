
#include "Matrix.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

//Matrix 4 X 4

Matrix::Matrix(float val)
{
	_00 = val; _01 = val; _02 = val; _03 = val;
	_10 = val; _11 = val; _12 = val; _13 = val;
	_20 = val; _21 = val; _22 = val; _23 = val;
	_30 = val; _31 = val; _32 = val; _33 = val;
}

Matrix::Matrix( const Matrix & mat)
{
	_00 = mat._00; _01 = mat._01; _02 = mat._02; _03 = mat._03;
	_10 = mat._10; _11 = mat._11; _12 = mat._12; _13 = mat._13;
	_20 = mat._20; _21 = mat._21; _22 = mat._22; _23 = mat._23;
	_30 = mat._30; _31 = mat._31; _32 = mat._32; _33 = mat._33;
}
void Matrix::SetUpVector(const Vector3 & up)
{
	upVector[0] = up.x;
	upVector[1] = up.y;
	upVector[2] = up.z;
	upVector[3] = 0.0f;
}
void Matrix::SetForwardVector(const Vector3 & forward)
{
	forwardVector[0] = forward.x;
	forwardVector[1] = forward.y;
	forwardVector[2] = forward.z;
	forwardVector[3] = 0.0f;
}
void Matrix::SetRightVector(const Vector3 & right)
{
	rightVector[0] = right.x;
	rightVector[1] = right.y;
	rightVector[2] = right.z;
	rightVector[3] = 0.0f;
}

void Matrix::SetTranslationVector(const Vector3 & translation)
{
	translationVector[0] = translation.x;
	translationVector[1] = translation.y;
	translationVector[2] = translation.z;
	translationVector[3] = 1.0f;
}
void Matrix::SetUpVector(const Vector4 & up)
{
	upVector[0] = up.x;
	upVector[1] = up.y;
	upVector[2] = up.z;
	upVector[3] = up.w;
}
void Matrix::SetForwardVector(const Vector4 & forward)
{
	forwardVector[0] = forward.x;
	forwardVector[1] = forward.y;
	forwardVector[2] = forward.z;
	forwardVector[3] = forward.w;
}
void Matrix::SetRightVector(const Vector4 & right)
{
	rightVector[0] = right.x;
	rightVector[1] = right.y;
	rightVector[2] = right.z;
	rightVector[3] = right.w;
}

void Matrix::SetTranslationVector(const Vector4 & translation)
{
	translationVector[0] = translation.x;
	translationVector[1] = translation.y;
	translationVector[2] = translation.z;
	translationVector[3] = translation.w;
}
Matrix & Matrix::SetLookAt(const Vector3 & eyePosition, const Vector3 & target, const Vector3 &up )
{
	Vector3 zaxis = ( eyePosition - target ).Normalize();
	Vector3 xaxis = ( up.Cross( zaxis )).Normalize();
	Vector3 yaxis = ( zaxis.Cross( xaxis ) ).Normalize();
	
	Matrix rotationMatrix, translationMatrix;

	rotationMatrix.SetRightVector(xaxis);
	rotationMatrix.SetUpVector(yaxis);
	rotationMatrix.SetForwardVector(zaxis);
	rotationMatrix.SetTranslationVector(Vector3(.0f, 0.0f, 0.0f));

	translationMatrix.SetTranslation( eyePosition );
	*this = ( translationMatrix * rotationMatrix ).Inverse();
	return *this;
}
Matrix & Matrix::SetRotationRollPitchYaw( float x, float y, float z )
{
	Matrix rotationXMatrix, rotationYMatrix, rotationZMatrix;
	rotationXMatrix.SetRotationX( x );
	rotationYMatrix.SetRotationY( y );
	rotationZMatrix.SetRotationZ( z );
	*this = rotationYMatrix * rotationXMatrix * rotationZMatrix;
	return *this;
}

Matrix & Matrix::SetRotationYawPitchRoll( float x, float y, float z )
{
	Matrix rotationXMatrix, rotationYMatrix, rotationZMatrix;
	rotationXMatrix.SetRotationX( x );
	rotationYMatrix.SetRotationY( y );
	rotationZMatrix.SetRotationZ( z );
	*this = rotationZMatrix * rotationXMatrix * rotationYMatrix;
	return *this;
}

Matrix & Matrix::SetZero()
{
	_00 = 0.0f; _01 = 0.0f; _02 = 0.0f; _03 = 0.0f;
	_10 = 0.0f; _11 = 0.0f; _12 = 0.0f; _13 = 0.0f;
	_20 = 0.0f; _21 = 0.0f; _22 = 0.0f; _23 = 0.0f;
	_30 = 0.0f; _31 = 0.0f; _32 = 0.0f; _33 = 0.0f;

	return *this;
}

Matrix & Matrix::SetIdentity()
{
	_00 = 1.0f; _01 = 0.0f; _02 = 0.0f; _03 = 0.0f;
	_10 = 0.0f; _11 = 1.0f; _12 = 0.0f; _13 = 0.0f;
	_20 = 0.0f; _21 = 0.0f; _22 = 1.0f; _23 = 0.0f;
	_30 = 0.0f; _31 = 0.0f; _32 = 0.0f; _33 = 1.0f;

	return *this;
}

Matrix & Matrix::SetRotationX(float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	_00 = 1.0f; _01 = 0.0f; _02 = 0.0f; _03 = 0.0f;
	_10 = 0.0f; _11 =    c; _12 =    s; _13 = 0.0f;
	_20 = 0.0f; _21 =   -s; _22 =    c; _23 = 0.0f;
	_30 = 0.0f; _31 = 0.0f; _32 = 0.0f; _33 = 1.0f;
	return *this;
}

Matrix & Matrix::SetRotationY(float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	_00 =    c; _01 = 0.0f; _02 =   -s; _03 = 0.0f;
	_10 = 0.0f; _11 = 1.0f; _12 = 0.0f; _13 = 0.0f;
	_20 =    s; _21 = 0.0f; _22 =    c; _23 = 0.0f;
	_30 = 0.0f; _31 = 0.0f; _32 = 0.0f; _33 = 1.0f;
	return *this;
}

Matrix & Matrix::SetRotationZ(float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	_00 =    c; _01 =    s; _02 = 0.0f; _03 = 0.0f;
	_10 =   -s; _11 =    c; _12 = 0.0f; _13 = 0.0f;
	_20 = 0.0f; _21 = 0.0f; _22 = 1.0f; _23 = 0.0f;
	_30 = 0.0f; _31 = 0.0f; _32 = 0.0f; _33 = 1.0f;
	return *this;
}

Matrix & Matrix::SetRotationAngleAxis( float angle, float x, float y, float z )
{
	float sinAngle, cosAngle;
	float mag = sqrtf(x * x + y * y + z * z);

	sinAngle = sinf ( angle );
	cosAngle = cosf ( angle );
	if ( mag > 0.0f )
	{
		float xx, yy, zz, xy, yz, zx, xs, ys, zs;
		float oneMinusCos;
		float magInv = 1.0f / mag;

		x *= magInv;
		y *= magInv;
		z *= magInv;

		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * sinAngle;
		ys = y * sinAngle;
		zs = z * sinAngle;
		oneMinusCos = 1.0f - cosAngle;

		_00 = (oneMinusCos * xx) + cosAngle;
		_10 = (oneMinusCos * xy) - zs;
		_20 = (oneMinusCos * zx) + ys;
		_30 = 0.0F;

		_01 = (oneMinusCos * xy) + zs;
		_11 = (oneMinusCos * yy) + cosAngle;
		_21 = (oneMinusCos * yz) - xs;
		_31 = 0.0F;

		_02 = (oneMinusCos * zx) - ys;
		_12 = (oneMinusCos * yz) + xs;
		_22 = (oneMinusCos * zz) + cosAngle;
		_32 = 0.0F;

		_03 = 0.0F;
		_13 = 0.0F;
		_23 = 0.0F;
		_33 = 1.0F;
		return * this;
	}
	else
		return SetIdentity();
}


Matrix & Matrix::SetScale(float scale)
{
	_00 = scale; _01 = 0.0f;  _02 = 0.0f;  _03 = 0.0f;
	_10 = 0.0f;  _11 = scale; _12 = 0.0f;  _13 = 0.0f;
	_20 = 0.0f;  _21 = 0.0f;  _22 = scale; _23 = 0.0f;
	_30 = 0.0f;  _31 = 0.0f;  _32 = 0.0f;  _33 = 1.0f;

	return *this;
}

Matrix & Matrix::SetScale(float scaleX, float scaleY, float scaleZ)
{
	_00 = scaleX; _01 = 0.0f;   _02 = 0.0f;   _03 = 0.0f;
	_10 = 0.0f;   _11 = scaleY; _12 = 0.0f;   _13 = 0.0f;
	_20 = 0.0f;   _21 = 0.0f;   _22 = scaleZ; _23 = 0.0f;
	_30 = 0.0f;   _31 = 0.0f;   _32 = 0.0f;   _33 = 1.0f;
	return *this;
}

Matrix & Matrix::SetScale(float * pScale)
{
	_00 = pScale[0];   _01 = 0.0f;        _02 = 0.0f;        _03 = 0.0f;
	_10 = 0.0f;        _11 = pScale[1];   _12 = 0.0f;        _13 = 0.0f;
	_20 = 0.0f;        _21 = 0.0f;        _22 = pScale[2];   _23 = 0.0f;
	_30 = 0.0f;        _31 = 0.0f;        _32 = 0.0f;        _33 = 1.0f;

	return *this;
}

Matrix & Matrix::SetScale( const Vector3 & scaleVec)
{
	_00 = scaleVec.x; _01 = 0.0f;       _02 = 0.0f;       _03 = 0.0f;
	_10 = 0.0f;       _11 = scaleVec.y; _12 = 0.0f;       _13 = 0.0f;
	_20 = 0.0f;       _21 = 0.0f;       _22 = scaleVec.z; _23 = 0.0f;
	_30 = 0.0f;       _31 = 0.0f;       _32 = 0.0f;       _33 = 1.0f;

	return *this;
}

Matrix & Matrix::SetTranslation(float x, float y, float z)
{
	_00 = 1.0f; _01 = 0.0f; _02 = 0.0f; _03 = 0.0f;
	_10 = 0.0f; _11 = 1.0f; _12 = 0.0f; _13 = 0.0f;
	_20 = 0.0f; _21 = 0.0f; _22 = 1.0f; _23 = 0.0f;
	_30 =    x; _31 =    y; _32 =    z; _33 = 1.0f;

	return *this;
}

Matrix & Matrix::SetTranslation( float *pTrans)
{
	_00 = 1.0f;      _01 = 0.0f;      _02 = 0.0f;      _03 = 0.0f;
	_10 = 0.0f;      _11 = 1.0f;      _12 = 0.0f;      _13 = 0.0f;
	_20 = 0.0f;      _21 = 0.0f;      _22 = 1.0f;      _23 = 0.0f;
	_30 = pTrans[0]; _31 = pTrans[1]; _32 = pTrans[2]; _33 = 1.0f;

	return *this;
}

Matrix & Matrix::SetTranslation( const Vector3 &vec )
{
	_00 =  1.0f; _01 =  0.0f; _02 =  0.0f; _03 = 0.0f;
	_10 =  0.0f; _11 =  1.0f; _12 =  0.0f; _13 = 0.0f;
	_20 =  0.0f; _21 =  0.0f; _22 =  1.0f; _23 = 0.0f;
	_30 = vec.x; _31 = vec.y; _32 = vec.z; _33 = 1.0f;

	return *this;
}

Matrix & Matrix::SetPerspective(float fovY, float aspect, float nearPlane, float farPlane)
{
	float height = 2.0f * nearPlane * tanf(fovY * 0.5f);
	float width = height * aspect;
	float n2 = 2.0f * nearPlane;
	float rcpnmf = 1.f / (nearPlane - farPlane);

	_00 = n2 / width;
	_10 = 0;
	_20 = 0;
	_30 = 0;

	_01 = 0;
	_11 = n2 / height;
	_21 = 0;
	_31 = 0;

	_02 = 0;
	_12 = 0;
	_22 = (farPlane + nearPlane) * rcpnmf;
	_32 = farPlane * rcpnmf * n2;

	_03 = 0;
	_13 = 0;
	_23 = -1.f;
	_33 = 0;

	return *this;
}
Matrix& Matrix::SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	float r_l = right - left;
    float t_b = top - bottom;
    float f_n = zFar - zNear;
    float tx = - (right + left) / (right - left);
    float ty = - (top + bottom) / (top - bottom);
    float tz = - (zFar + zNear) / (zFar - zNear);
    
    _00 = 2.0f / r_l;
	_10 = 0;
	_20 = 0;
	_30 = tx;

	_01 = 0;
	_11 = 2.0f / t_b;;
	_21 = 0;
	_31 = ty;

	_02 = 0;
	_12 = 0;
	_22 = -2.0f / f_n;
	_32 = tz;

	_03 = 0;
	_13 = 0;
	_23 = 0;
	_33 = 1.0f;
	
	return *this;
}
Matrix Matrix::Transpose() const 
{
	Matrix res;
	res._00 = _00; res._01 = _10; res._02 = _20; res._03 = _30;
	res._10 = _01; res._11 = _11; res._12 = _21; res._13 = _31;
	res._20 = _02; res._21 = _12; res._22 = _22; res._23 = _32;
	res._30 = _03; res._31 = _13; res._32 = _23; res._33 = _33;
	return res;
}
Matrix & Matrix::SetTranspose() 
{
	*this = this->Transpose();
	return *this;
}
Matrix Matrix::operator + ( const Matrix & mat) const 
{
	Matrix res( *this );
	res += mat;
	return res;
}

Matrix & Matrix::operator += ( const Matrix & mat)
{
	_00 += mat._00; _01 += mat._01; _02 += mat._02; _03 += mat._03;
	_10 += mat._10; _11 += mat._11; _12 += mat._12; _13 += mat._13;
	_20 += mat._20; _21 += mat._21; _22 += mat._22; _23 += mat._23;
	_30 += mat._30; _31 += mat._31; _32 += mat._32; _33 += mat._33;

	return *this;
}

Matrix Matrix::operator - ( const Matrix & mat) const 
{
	Matrix res( *this );
	res -= mat;
	return res;
}

Matrix & Matrix::operator -= ( const Matrix & mat)
{
	_00 -= mat._00; _01 -= mat._01; _02 -= mat._02; _03 -= mat._03;
	_10 -= mat._10; _11 -= mat._11; _12 -= mat._12; _13 -= mat._13;
	_20 -= mat._20; _21 -= mat._21; _22 -= mat._22; _23 -= mat._23;
	_30 -= mat._30; _31 -= mat._31; _32 -= mat._32; _33 -= mat._33;

	return *this;
}

Matrix Matrix::operator * ( const Matrix & mat) const 
{
	Matrix res;
	res._00 = _00 * mat._00 + _10 * mat._01 + _20 * mat._02 + _30 * mat._03;
	res._10 = _00 * mat._10 + _10 * mat._11 + _20 * mat._12 + _30 * mat._13;
	res._20 = _00 * mat._20 + _10 * mat._21 + _20 * mat._22 + _30 * mat._23;
	res._30 = _00 * mat._30 + _10 * mat._31 + _20 * mat._32 + _30 * mat._33;

	res._01 = _01 * mat._00 + _11 * mat._01 + _21 * mat._02 + _31 * mat._03;
	res._11 = _01 * mat._10 + _11 * mat._11 + _21 * mat._12 + _31 * mat._13;
	res._21 = _01 * mat._20 + _11 * mat._21 + _21 * mat._22 + _31 * mat._23;
	res._31 = _01 * mat._30 + _11 * mat._31 + _21 * mat._32 + _31 * mat._33;

	res._02 = _02 * mat._00 + _12 * mat._01 + _22 * mat._02 + _32 * mat._03;
	res._12 = _02 * mat._10 + _12 * mat._11 + _22 * mat._12 + _32 * mat._13;
	res._22 = _02 * mat._20 + _12 * mat._21 + _22 * mat._22 + _32 * mat._23;
	res._32 = _02 * mat._30 + _12 * mat._31 + _22 * mat._32 + _32 * mat._33;

	res._03 = _03 * mat._00 + _13 * mat._01 + _23 * mat._02 + _33 * mat._03;
	res._13 = _03 * mat._10 + _13 * mat._11 + _23 * mat._12 + _33 * mat._13;
	res._23 = _03 * mat._20 + _13 * mat._21 + _23 * mat._22 + _33 * mat._23;
	res._33 = _03 * mat._30 + _13 * mat._31 + _23 * mat._32 + _33 * mat._33;

	return res;
}

Matrix Matrix::operator * (float k) const 
{
	Matrix mat( *this );
	mat *= k;
	return mat;
}

Matrix & Matrix::operator *= (float k)
{
	_00 *= k; _01 *= k; _02 *= k; _03 *= k;
	_10 *= k; _11 *= k; _12 *= k; _13 *= k;
	_20 *= k; _21 *= k; _22 *= k; _23 *= k;
	_30 *= k; _31 *= k; _32 *= k; _33 *= k;

	return *this;
}


Vector4 Matrix::operator * ( const Vector4 & vec) const 
{
	Vector4 res;

	res.x = vec.x * _00 + vec.y * _10 + vec.z * _20 + vec.w * _30;
	res.y = vec.x * _01 + vec.y * _11 + vec.z * _21 + vec.w * _31;
	res.z = vec.x * _02 + vec.y * _12 + vec.z * _22 + vec.w * _32;
	res.w = vec.x * _03 + vec.y * _13 + vec.z * _23 + vec.w * _33;
	
	return res;
}

Matrix & Matrix::operator = ( const Matrix & mat)
{
	_00 = mat._00; _01 = mat._01; _02 = mat._02; _03 = mat._03;
	_10 = mat._10; _11 = mat._11; _12 = mat._12; _13 = mat._13;
	_20 = mat._20; _21 = mat._21; _22 = mat._22; _23 = mat._23;
	_30 = mat._30; _31 = mat._31; _32 = mat._32; _33 = mat._33;

	return *this;
}

float Matrix::Determinant() const
{
	return _00*_11*_22*_33 - _00*_11*_23*_32 + _00*_12*_23*_31 - _00*_12*_21*_33
		 + _00*_13*_21*_32 - _00*_13*_22*_31 - _01*_12*_23*_30 + _01*_12*_20*_33
		 - _01*_13*_20*_32 + _01*_13*_22*_30 - _01*_10*_22*_33 + _01*_10*_23*_32
		 + _02*_13*_20*_31 - _02*_13*_21*_30 + _02*_10*_21*_33 - _02*_10*_23*_31
		 + _02*_11*_23*_30 - _02*_11*_20*_33 - _03*_10*_21*_32 + _03*_10*_22*_31
		 - _03*_11*_22*_30 + _03*_11*_20*_32 - _03*_12*_20*_31 + _03*_12*_21*_30;
}
Matrix & Matrix::SetInverse()
{
	*this = this->Inverse();
	return *this;
}
Matrix Matrix::Inverse() const
{
	// Compute the reciprocal determinant
	float det = Determinant();
	if(det < 0.00001f) 
	{
		// Matrix not invertible				
		return *this;
	}

	float invdet = 1.0f / det;

	Matrix res;
	res._00 = invdet  * (_11 * (_22 * _33 - _23 * _32) + _12 * (_23 * _31 - _21 * _33) + _13 * (_21 * _32 - _22 * _31));
	res._01 = -invdet * (_01 * (_22 * _33 - _23 * _32) + _02 * (_23 * _31 - _21 * _33) + _03 * (_21 * _32 - _22 * _31));
	res._02 = invdet  * (_01 * (_12 * _33 - _13 * _32) + _02 * (_13 * _31 - _11 * _33) + _03 * (_11 * _32 - _12 * _31));
	res._03 = -invdet * (_01 * (_12 * _23 - _13 * _22) + _02 * (_13 * _21 - _11 * _23) + _03 * (_11 * _22 - _12 * _21));
	res._10 = -invdet * (_10 * (_22 * _33 - _23 * _32) + _12 * (_23 * _30 - _20 * _33) + _13 * (_20 * _32 - _22 * _30));
	res._11 = invdet  * (_00 * (_22 * _33 - _23 * _32) + _02 * (_23 * _30 - _20 * _33) + _03 * (_20 * _32 - _22 * _30));
	res._12 = -invdet * (_00 * (_12 * _33 - _13 * _32) + _02 * (_13 * _30 - _10 * _33) + _03 * (_10 * _32 - _12 * _30));
	res._13 = invdet  * (_00 * (_12 * _23 - _13 * _22) + _02 * (_13 * _20 - _10 * _23) + _03 * (_10 * _22 - _12 * _20));
	res._20 = invdet  * (_10 * (_21 * _33 - _23 * _31) + _11 * (_23 * _30 - _20 * _33) + _13 * (_20 * _31 - _21 * _30));
	res._21 = -invdet * (_00 * (_21 * _33 - _23 * _31) + _01 * (_23 * _30 - _20 * _33) + _03 * (_20 * _31 - _21 * _30));
	res._22 = invdet  * (_00 * (_11 * _33 - _13 * _31) + _01 * (_13 * _30 - _10 * _33) + _03 * (_10 * _31 - _11 * _30));
	res._23 = -invdet * (_00 * (_11 * _23 - _13 * _21) + _01 * (_13 * _20 - _10 * _23) + _03 * (_10 * _21 - _11 * _20));
	res._30 = -invdet * (_10 * (_21 * _32 - _22 * _31) + _11 * (_22 * _30 - _20 * _32) + _12 * (_20 * _31 - _21 * _30));
	res._31 = invdet  * (_00 * (_21 * _32 - _22 * _31) + _01 * (_22 * _30 - _20 * _32) + _02 * (_20 * _31 - _21 * _30));
	res._32 = -invdet * (_00 * (_11 * _32 - _12 * _31) + _01 * (_12 * _30 - _10 * _32) + _02 * (_10 * _31 - _11 * _30));
	res._33 = invdet  * (_00 * (_11 * _22 - _12 * _21) + _01 * (_12 * _20 - _10 * _22) + _02 * (_10 * _21 - _11 * _20));
	return res;
}
