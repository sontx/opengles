#ifdef WIN32
#include "GL.h"
#include "WinSurface.h"
#include "Shader.h"
#include "Vertex.h"
//#include <time.h>
//#include <math.h>

#define SCREEN_W 420
#define SCREEN_H 720

Shader * shader;
//long t_start;

void Init()
{
	shader = new Shader("Basic.vs", "Basic.fs");
	shader->Init();
	glUseProgram(shader->mProgram);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	Vertex * vertices = new Vertex[3];
	// red point
	vertices[0].position.x = 0.0f;
	vertices[0].position.y = 0.5f;
	vertices[0].position.z = 0.0f;
	vertices[0].color.x = 1.0f;// r
	vertices[0].color.y = 0.0f;// b
	vertices[0].color.z = 0.0f;// g

	// green point
	vertices[1].position.x = 0.5f;
	vertices[1].position.y = -0.5f;
	vertices[1].position.z = 0.0f;
	vertices[1].color.x = 0.0f;// r
	vertices[1].color.y = 1.0f;// b
	vertices[1].color.z = 0.0f;// g

	// blue point
	vertices[2].position.x = -0.5f;
	vertices[2].position.y = -0.5f;
	vertices[2].position.z = 0.0f;
	vertices[2].color.x = 0.0f;// r
	vertices[2].color.y = 0.0f;// b
	vertices[2].color.z = 1.0f;// g

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, vertices, GL_STATIC_DRAW);

	MEM_FREE1D(vertices);

	glVertexAttribPointer(shader->m_a_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	glEnableVertexAttribArray(shader->m_a_position);
	glVertexAttribPointer(shader->m_a_color, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
	glEnableVertexAttribArray(shader->m_a_color);

	//t_start = clock();
}

void Update()
{
	//long t_now = clock();
	//double dental = t_now - t_start;
	//glUniform3f(shader->m_u_color, sin(dental * 0.01f), 0.0f, 0.0f);
}

void Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
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