#pragma once
#include "Vector2.h"
//Vector3

class Vector3
{
public:
	//Constructors
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3(float * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]) {}
	Vector3( const Vector3 & vector) : x(vector.x), y(vector.y), z(vector.z) {}
	//Vector's operations
	float Length() const ;
	Vector3 & Normalize();
	Vector3 operator + ( const Vector3 & vector) const ;
	Vector3 & operator += ( const Vector3 & vector);
	Vector3 operator - () const ;
	Vector3 operator - ( const Vector3 & vector) const ;
	Vector3 & operator -= ( const Vector3 & vector);
	Vector3 operator * (float k) const ;
	Vector3 & operator *= (float k);
	Vector3 operator / (float k) const ;
	Vector3 & operator /= (float k);
	Vector3 & operator = ( const Vector3 & vector);
	Vector3 & operator = (float* pArg);
	bool operator == (const Vector3 & vector) const;
	Vector3 Modulate( const Vector3 & vector) const ;
	float Dot( const Vector3 & vector) const ;
	Vector3 Cross( const Vector3 & vector) const ;

	//access to elements
	float operator [] (unsigned int idx) const ;

	// data members
	union
	{
		struct
		{
			float xy[2];
		};
		struct
		{
			float x;
			float y;
			float z;
		};
	};
};

