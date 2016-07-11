#pragma once

#include "Vector4.h"
#define DEGREES_TO_RADIANS(x) (x*0.017453292f)
class Matrix;

class Matrix
{
public:
	//constructors
	Matrix(){this->SetIdentity();}
	Matrix(float val);
	Matrix( const Matrix & mat);

	// Matrix operations
	Matrix & SetZero();
	Matrix & SetIdentity();
	
	void SetUpVector(const Vector4 & up);
	void SetForwardVector(const Vector4 & forward);
	void SetRightVector(const Vector4 & right);
	void SetTranslationVector(const Vector4 & translation);

	void SetUpVector(const Vector3 & up);
	void SetForwardVector(const Vector3 & forward);
	void SetRightVector(const Vector3 & right);
	void SetTranslationVector(const Vector3 & translation);
	
	Matrix & SetLookAt(const Vector3 & eyePosition, const Vector3 & target, const Vector3 &up = Vector3(0.0f, 1.0f, 0.0f));
	Matrix & SetRotationX(float angle);
	Matrix & SetRotationY(float angle);
	Matrix & SetRotationZ(float angle);
	Matrix & SetRotationAngleAxis( float angle, float x, float y, float z );
	Matrix & SetRotationRollPitchYaw( float x, float y, float z );
	Matrix & SetRotationYawPitchRoll( float x, float y, float z );
	//Rotaion with roll - pitch - yaw rules


	Matrix & SetScale(float scale);
	Matrix & SetScale(float scaleX, float scaleY, float scaleZ);
	Matrix & SetScale(float * pScale);
	Matrix & SetScale( const Vector3 &scaleVec);

	Matrix & SetTranslation(float x, float y, float z);
	Matrix & SetTranslation(float *pTrans);
	Matrix & SetTranslation( const Vector3 &vec);
	Matrix & SetTranspose();
	Matrix & SetInverse();
	Matrix & SetPerspective(float fovY, float aspect, float nearPlane, float farPlane);
	Matrix& SetOrtho(float left, float right, float bottom, float top, float near, float far);
	float Determinant() const;
	Matrix Transpose() const;
	Matrix Inverse() const;

	Matrix operator + ( const Matrix & mat) const ;
	Matrix & operator += ( const Matrix & mat);
	Matrix operator - ( const Matrix & mat) const ;
	Matrix &operator -= ( const Matrix & mat);

	Matrix operator * ( const Matrix & mat) const ;
	Matrix operator * (float k) const ;
	Matrix & operator *= (float k);

	Vector4 operator * ( const Vector4 & vec) const ;

	Matrix & operator = ( const Matrix & mat);
	float * ToArray()
	{
		return m;
	}
	
	//data members
	union
	{
		float mm[4][4];
		float m[16];
		struct
		{
			float rightVector[4];
			float upVector[4];
			float forwardVector[4];
			float translationVector[4];
		};
		struct 
		{
			float _00, _01, _02, _03;
			float _10, _11, _12, _13;
			float _20, _21, _22, _23;
			float _30, _31, _32, _33;
		};
	};
};
