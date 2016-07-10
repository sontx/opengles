#ifdef WIN32
#include "GL.h"
#include "WinSurface.h"

#define SCREEN_W 420
#define SCREEN_H 720

void Init()
{
}

void Update()
{
}

void Draw()
{
}

void Destroy()
{
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