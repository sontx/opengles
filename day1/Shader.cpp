#include "Shader.h"
#include <string.h>

GLuint Shader::LoadProgram(GLuint vertexShader, GLuint fragmentShader)
{
	// create program
	GLuint programObject = glCreateProgram();
	if (programObject == 0)
		return 0;

	// attach the shaders to the program
	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	glLinkProgram(programObject);

	// check success
	GLint linked;
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLint infoLength = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLength);
		if (infoLength > 1)
		{
			char * infoLog = new char[sizeof(char) * infoLength];
			glGetProgramInfoLog(programObject, infoLength, NULL, infoLog);
			LOG(infoLog);
			MEM_FREE1D(infoLog);
		}
		glDeleteProgram(programObject);
		return 0;
	}

	return programObject;
}

GLuint Shader::LoadShader(GLenum type, const char * shaderFile)
{
	// create shader
	GLuint shader = glCreateShader(type);
	if (shader == 0)
		return 0;
	
	// read shader file content to string
	FILE * pf = fopen(shaderFile, "rb");
	if (pf == NULL)
		return 0;

	fseek(pf, 0, SEEK_END);
	long size = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	char * buffer = new char[size + 1];
	fread(buffer, sizeof(char), size, pf);
	buffer[size] = '\0';
	fclose(pf);

	// compile shader
	glShaderSource(shader, 1, (const char **)&buffer, NULL);
	MEM_FREE1D(buffer);
	glCompileShader(shader);

	// test compilation error
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint infoLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
		if (infoLength > 1)
		{
			char * infoLog = new char[sizeof(char) * infoLength];
			glGetShaderInfoLog(shader, infoLength, NULL, infoLog);
			LOG(infoLog);
			MEM_FREE1D(infoLog);
		}
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

void Shader::FindLocations()
{
	m_a_position = glGetAttribLocation(mProgram, "a_position");
	m_a_uv = glGetAttribLocation(mProgram, "a_uv");
	m_u_color = glGetUniformLocation(mProgram, "u_color");
	m_u_texture = glGetUniformLocation(mProgram, "u_texture");
}

bool Shader::Init()
{
	GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, mVertexShaderFile);
	MEM_FREE(mVertexShaderFile);
	if (vertexShader == 0)
	{
		LOG("Loading %s fail.", mVertexShaderFile);
		return false;
	}

	GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, mFragmentShaderFile);
	MEM_FREE(mFragmentShaderFile);
	if (vertexShader == 0)
	{
		LOG("Loading %s fail.", mFragmentShaderFile);
		return false;
	}
	
	GLuint program = LoadProgram(vertexShader, fragmentShader);
	if (program == 0)
	{
		LOG("Create program fail.");
		return false;
	}

	mProgram = program;
	FindLocations();

	return true;
}

Shader::Shader(const char * vertexShaderFile, const char * fragmentShaderFile)
{
	mVertexShaderFile = strdup(vertexShaderFile);
	mFragmentShaderFile = strdup(fragmentShaderFile);
}

Shader::~Shader()
{
}