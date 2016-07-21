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
	GLint m_a_position;
	GLint m_a_uv;
	GLint m_u_color;
	GLint m_u_texture;
	bool Init();
	Shader(const char * vertexShaderFile, const char * fragmentShaderFile);
	virtual ~Shader();
};
