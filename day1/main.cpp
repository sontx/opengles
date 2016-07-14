#ifdef WIN32
#include "GL.h"
#include "WinSurface.h"
#include "Shader.h"
#include "Vertex.h"

#define SCREEN_W 420
#define SCREEN_H 720

Shader * shader;

void Init()
{
	shader = new Shader("Basic.vs", "Basic.fs");
	shader->Init();
	glUseProgram(shader->mProgram);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	Vertex * vertices = new Vertex[3];
	vertices[0].position.x = 0.0f;
	vertices[0].position.y = 0.5f;
	vertices[0].position.z = 0.0f;

	vertices[1].position.x = 0.5f;
	vertices[1].position.y = -0.5f;
	vertices[1].position.z = 0.0f;

	vertices[2].position.x = -0.5f;
	vertices[2].position.y = -0.5f;
	vertices[2].position.z = 0.0f;

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, vertices, GL_STATIC_DRAW);

	MEM_FREE1D(vertices);

	glVertexAttribPointer(shader->m_a_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	glEnableVertexAttribArray(shader->m_a_position);

	GLuint indices[] = { 0, 1, 2 };
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Update()
{
}

void Draw()
{
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
}

void Destroy()
{
	MEM_FREE(shader);
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