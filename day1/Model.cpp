#include "Model.h"
#include "Vertex.h"
#include <string.h>

int Model::GetModelFileType(const char * filePath)
{
	int length = strlen(filePath);
	const char * extension = filePath + (length - 3);
	if (strcmp(extension, "nfg") == 0 || strcmp(extension, "NFG") == 0)
		return MODEL_NFG;
	else if (strcmp(extension, "got") == 0 || strcmp(extension, "got") == 0)
		return MODEL_GOT;
	return MODEL_UND;
}

bool Model::InitNFG(FILE * file)
{
	int numberOfVertices;
	fscanf(file, "NrVertices: %d\n", &numberOfVertices);
	if (numberOfVertices <= 0)
		return false;
	Vertex * vertices = new Vertex[numberOfVertices];
	for (int i = 0; i < numberOfVertices; ++i)
	{
		fscanf(file, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];\n",
				&vertices[i].position.x, &vertices[i].position.y, &vertices[i].position.z,
				&vertices[i].normal.x, &vertices[i].normal.y, &vertices[i].normal.z,
				&vertices[i].uv.x, &vertices[i].uv.y);
	}
	glGenBuffers(1, &this->mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numberOfVertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	MEM_FREE1D(vertices);

	int numberOfIndices;
	fscanf(file, "NrIndices: %d\n", &numberOfIndices);
	if (numberOfIndices <= 0)
	{
		glDeleteBuffers(1, &mVBO);
		return 0;
	}
	int * indices = new int[numberOfIndices];
	for (int i = 0; i < numberOfIndices; i += 3)
	{
		fscanf(file, "   %*d.    %d,    %d,    %d\n", &indices[i], &indices[i + 1], &indices[i + 2]);
	}
	glGenBuffers(1, &this->mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * numberOfIndices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	MEM_FREE1D(indices);
	mNumberOfIndices = numberOfIndices;
}

void Model::Init()
{
	LOG("Loading %s...", mModelFile);
	FILE * file = fopen(mModelFile, "rb");
	if (file != NULL)
	{
		int modelType = GetModelFileType(mModelFile);
		bool result = false;
		switch (modelType)
		{
		case MODEL_NFG:
			result = InitNFG(file);
			break;
		case MODEL_GOT:
			break;
		default:
			LOG("Model file format do not support");
			break;
		}
		LOG("%s", result ? "OK" : "FAIL");
		fclose(file);
	}
	else
	{
		LOG("Can not open file");
	}
	MEM_FREE(mModelFile);
}

Model::Model(const char * modelFile)
{
	mModelFile = strdup(modelFile);
}

Model::~Model()
{
	MEM_FREE(mModelFile);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mIBO);
}
