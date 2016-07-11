#pragma once
//Vector2

class Vector2
{
public:
	//Constructors
	Vector2() : x(0.0f), y(0.0f){}
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	Vector2(float * pArg) : x(pArg[0]), y(pArg[1]) {}
	Vector2( const Vector2 & vector) : x(vector.x), y(vector.y) {}

	//Vector's operations
	float Length() const;
	Vector2 & Normalize();
	Vector2 operator + ( const Vector2 & vector) const;
	Vector2 & operator += ( const Vector2 & vector);
	Vector2 operator - () const;
	Vector2 operator - ( const Vector2 & vector) const;
	Vector2 & operator -= ( const Vector2 & vector);
	Vector2 operator * (float k) const;
	Vector2 & operator *= (float k);
	Vector2 operator / (float k) const;
	Vector2 & operator /= (float k);
	Vector2 & operator = ( const Vector2 & vector);
	Vector2 & operator = (float* pArg);
	Vector2 Modulate( const Vector2 & vector) const;
	float Dot( const Vector2 & vector) const;

	//access to elements
	float operator [] (unsigned int idx) const;

	//data members
	float x;
	float y;
};
