#pragma once
#include "GL.h"

class Model
{
private:
	static const int MODEL_UND = 0;
	static const int MODEL_NFG = 1;
	static const int MODEL_GOT = 2;
	char * mModelFile;
	int GetModelFileType(const char * filePath);
	bool InitNFG(FILE * file);
public:
	GLuint mVBO;
	GLuint mIBO;
	int mNumberOfIndices;
	void Init();
	Model(const char * modelFile);
	~Model();
};
