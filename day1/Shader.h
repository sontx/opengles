#pragma once
#include "GL.h"

class Shader
{
private:
	char * mVertexShaderFile;
	char * mFragmentShaderFile;

	GLuint LoadProgram(GLuint vertexShader, GLuint fragmentShader);
	GLuint LoadShader(GLenum type, const char * shaderFile);
	void FindLocations();
public:
	GLuint mProgram;
	GLuint m_a_position;
	GLuint m_u_color;
	bool Init();
	Shader(const char * vertexShaderFile, const char * fragmentShaderFile);
	virtual ~Shader();
};
