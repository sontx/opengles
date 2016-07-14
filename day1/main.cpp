#ifdef WIN32
#include "GL.h"
#include "WinSurface.h"
#include "Shader.h"
#include "Vertex.h"
#include "Model.h"

#define SCREEN_W 420
#define SCREEN_H 720

Shader * shader;
Model * model;

void Init()
{
	shader = new Shader("Basic.vs", "Basic.fs");
	shader->Init();
	model = new Model("../res/models/Woman2.nfg");
	model->Init();

	glUseProgram(shader->mProgram);
	glBindBuffer(GL_ARRAY_BUFFER, model->mVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->mIBO);

	glVertexAttribPointer(shader->m_a_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	glEnableVertexAttribArray(shader->m_a_position);
}

void Update()
{
}

void Draw()
{
	glDrawElements(GL_TRIANGLES, model->mNumberOfIndices, GL_UNSIGNED_INT, 0);
}

void Destroy()
{
	MEM_FREE(shader);
	MEM_FREE(model);
}

void Key(int keyCode, bool isKeyDown)
{
}

void Mouse(int type, int x, int y)
{
}

int main()
{
	InitWindow(SCREEN_W, SCREEN_H);

	RegisterInitFunc(Init);
	RegisterDrawFunc(Draw);
	RegisterUpdateFunc(Update);	
	RegisterDestroyFunc(Destroy);
	RegisterKeyFunc(Key);
	RegisterMouseFunc(Mouse);

	WinLoop();
	
	return 0;
}

#endif