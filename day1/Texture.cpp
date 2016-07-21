#include "Texture.h"
#include "TGA.h"

void Texture::ConfigTexture()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTiling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTiling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::Init()
{
	int width = 0;
	int height = 0;
	int bpp = 0;
	const char * imageData = LoadTGA(mTgaFilePath, width, height, bpp);
	LOG("Loaded texture %dx%d, %dbpp, %s", width, height, bpp, mTgaFilePath);
	MEM_FREE1D(mTgaFilePath);

	GLenum format = (bpp == 24 ? GL_RGB : GL_RGBA);

	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
	MEM_FREE1D(imageData);

	ConfigTexture();
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const char * tgaFilePath, GLenum tiling)
{
	mTgaFilePath = strdup(tgaFilePath);
	mTiling = tiling;
}

Texture::~Texture()
{
	MEM_FREE1D(mTgaFilePath);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &mTextureId);
}
