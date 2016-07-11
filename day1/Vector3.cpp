#include "Vector3.h"
#include "Matrix.h"
#include <stdio.h>
#include <math.h>

//Vector3

float Vector3::Length() const 
{
	return sqrt(x*x + y*y + z*z);
}

Vector3 & Vector3::Normalize()
{
	if ( Length() == 0.0f )
	{
		return *this;
	}
	float lenInv = 1.0f / Length();
	x *= lenInv;
	y *= lenInv;
	z *= lenInv;

	return *this;
}

Vector3 Vector3::operator + ( const Vector3 & vector) const 
{
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3 & Vector3::operator += ( const Vector3 & vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

Vector3 Vector3::operator - () const 
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator - ( const Vector3 & vector) const 
{
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3 & Vector3::operator -= ( const Vector3 & vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

Vector3 Vector3::operator * (float k) const 
{
	return Vector3(x * k, y * k, z * k);
}

Vector3 & Vector3::operator *= (float k)
{
	x *= k;
	y *= k;
	z *= k;

	return *this;
}

Vector3 Vector3::operator / (float k) const 
{
	float kInv = 1.0f / k;
	return Vector3(x * kInv, y * kInv, z * kInv);
}
	
Vector3 & Vector3::operator /= (float k)
{
	return operator *= (1.0f / k);
}

Vector3 & Vector3::operator = ( const Vector3 & vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	
	return *this;
}
bool Vector3::operator == (const Vector3 & vector) const
{
	if ( this->x == vector.x && y == vector.y && z == vector.z )
		return true;
	return false;
}
float Vector3::operator [] (unsigned int idx) const 
{
	return (&x)[idx];
}
Vector3 & Vector3::operator = (float* pArg)
{
	x = pArg[0];
	y = pArg[1];
	z = pArg[2];
	return *this;
}
Vector3 Vector3::Modulate( const Vector3 & vector) const 
{
	return Vector3(x * vector.x, y * vector.y, z * vector.z);
}

float Vector3::Dot( const Vector3 & vector) const 
{
	return x * vector.x + y * vector.y + z * vector.z;
}

Vector3 Vector3::Cross( const Vector3 & vector) const 
{
	return Vector3(y * vector.z -  z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x);
}
