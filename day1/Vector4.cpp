
#include "Matrix.h"
#include <math.h>


//Vector4

float Vector4::Length() const 
{
	return sqrt(x*x + y*y + z*z + w*w);
}

Vector4 & Vector4::Normalize()
{
	if ( Length() == 0.0f )
	{
		return *this;
	}
	float lenInv = 1.0f / Length();
	x *= lenInv;
	y *= lenInv;
	z *= lenInv;
	w *= lenInv;

	return *this;
}

Vector4 Vector4::operator + ( const Vector4 & vector) const 
{
	return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
}

Vector4 & Vector4::operator += ( const Vector4 & vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;

	return *this;
}

Vector4 Vector4::operator - () const 
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator - ( const Vector4 & vector) const 
{
	return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
}

Vector4 & Vector4::operator -= ( const Vector4 & vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;

	return *this;
}

Vector4 Vector4::operator * (float k) const 
{
	return Vector4(x * k, y * k, z * k, w * k);
}

Vector4 & Vector4::operator *= (float k)
{
	x *= k;
	y *= k;
	z *= k;
	w *= k;

	return *this;
}

Vector4 Vector4::operator / (float k) const 
{
	float kInv = 1.0f / k;
	return Vector4(x * kInv, y * kInv, z * kInv, w * kInv);
}

Vector4 & Vector4::operator /= (float k)
{
	return operator *= (1.0f / k);
}
Vector4 & Vector4::operator = (float* pArg)
{
	x = pArg[0];
	y = pArg[1];
	z = pArg[2];
	return *this;
}
Vector4 & Vector4::operator = ( const Vector4 & vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
	return *this;
}

float Vector4::operator [] (unsigned int idx) const 
{
	return (&x)[idx];
}

Vector4 Vector4::Modulate( const Vector4 & vector) const 
{
	return Vector4(x * vector.x, y * vector.y, z * vector.z, w * vector.w);
}

float Vector4::Dot( const Vector4 & vector) const 
{
	return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
}


Vector4 Vector4::operator * (  const Matrix & m ) const 
{
	Vector4 res;
	res.x = x * m._00 + y * m._10 + z * m._20 + w * m._30;
	res.y = x * m._01 + y * m._11 + z * m._21 + w * m._31;
	res.z = x * m._02 + y * m._12 + z * m._22 + w * m._32;
	res.w = x * m._03 + y * m._13 + z * m._23 + w * m._33;

	return res;
}
bool Vector4::operator == (const Vector4 & vector) const
{
	if ( this->x == vector.x && y == vector.y && z == vector.z && w == vector.w )
		return true;
	return false;
}