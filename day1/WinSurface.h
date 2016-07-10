#if WIN32

#pragma once

struct ESContext
{
	void (*OnKey)(int, bool);
	void (*OnMouse)(int type, int x, int y);
	void (*OnDraw)(void);
	void (*OnUpdate)(void);
	void (*OnInit)(void);
	void (*OnDestroy)(void);
};

void WinLoop();
bool InitWindow(int width, int height);
void RegisterInitFunc(void (*OnInit)(void));
void RegisterDrawFunc(void (*OnDraw)(void));
void RegisterUpdateFunc(void (*OnUpdate)(void));
void RegisterDestroyFunc(void (*OnDestroy)(void));
void RegisterKeyFunc(void (*OnKey)(int, bool));
void RegisterMouseFunc(void (*OnMouse)(int type, int x, int y));

#endif