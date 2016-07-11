#pragma once
//Vector4
#include "Vector3.h"

class Matrix;

class Vector4
{
public:
	//Constructors
	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(1.0f){}
	Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	Vector4(float * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]), w(pArg[3]) {}
	Vector4( const Vector3 & vector) : x(vector.x), y(vector.y), z(vector.z), w(1.0f) {}
	Vector4( const Vector3 & vector, float _w) : x(vector.x), y(vector.y), z(vector.z), w(_w) {}
	Vector4( const Vector4 & vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}

	//Vector's operations
	float Length() const ;
	Vector4 & Normalize();
	Vector4 operator + ( const Vector4 & vector) const ;
	Vector4 & operator += ( const Vector4 & vector);
	Vector4 operator - () const ;
	Vector4 operator - ( const Vector4 & vector) const ;
	Vector4 & operator -= ( const Vector4 & vector);
	Vector4 operator * (float k) const ;
	Vector4 & operator *= (float k);
	Vector4 operator / (float k) const ;
	Vector4 & operator /= (float k);
	Vector4 & operator = (float* pArg);
	Vector4 & operator = ( const Vector4 & vector);
	bool operator == (const Vector4 & vector) const;
	Vector4 Modulate( const Vector4 & vector) const ;
	float Dot( const Vector4 & vector) const ;

	//matrix multiplication
	Vector4 operator * ( const  Matrix & m ) const ;

	//access to elements
	float operator [] (unsigned int idx) const ;

	//data members
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct
		{
			float xyz[3];
		};
		struct
		{
			float xy[2];
		};
	};
};

