#pragma once
#include "GL.h"

class Texture
{
private:
	char * mTgaFilePath;
	GLenum mTiling;
	void ConfigTexture();
public:
	GLuint mTextureId;
	void Init();
	Texture(const char * tgaFilePath, GLenum tiling = GL_REPEAT);
	~Texture();
};
