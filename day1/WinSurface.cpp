#if WIN32

#include "WinSurface.h"
#include "GL.h"

static EGLDisplay			eglDisplay;
static EGLConfig			eglConfig;
static EGLSurface			eglSurface;
static EGLContext			eglContext;
static EGLNativeWindowType	eglWindow;
static ESContext context_tt;

/// helper functions

ATOM static RegisterWindow(WNDPROC windowProc, HINSTANCE hInstance)
{	
	WNDCLASS wndClass;
	memset(&wndClass, 0, sizeof(WNDCLASS));
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = windowProc;
	wndClass.hInstance = hInstance;
	wndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndClass.lpszClassName = CLASS_NAME;
	
	ATOM registerClass = RegisterClass(&wndClass);
	return registerClass;
}

HWND static CreateGLWindow(int width, int height, HINSTANCE hInstance)
{
	RECT rect;
	SetRect(&rect, 0, 0, width, height);
	AdjustWindowRectEx(&rect, WS_CAPTION | WS_SYSMENU, false, 0);

	HWND hwnd = CreateWindow(CLASS_NAME, WINDOW_NAME,
		WS_VISIBLE | WS_SYSMENU, 
		0, 0, rect.right - rect.left, rect.bottom - rect.top, 
		NULL, NULL, hInstance, NULL);
	
	return hwnd;
}

void static CleanWindow(EGLDisplay glDisplay, HWND hwnd, HDC hdc)
{
	eglMakeCurrent(glDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglTerminate(glDisplay);
	if (hdc)
		ReleaseDC(hwnd, hdc);
	if (hwnd)
		DestroyWindow(hwnd);
}

EGLDisplay static InitializeGLDisplay(HWND hwnd, HDC * outHDC)
{
	HDC hdc = GetDC(hwnd);
	if (!hdc)
	{
		MessageBox(NULL, "Failed to create the device context", WINDOW_NAME, MB_OK | MB_ICONEXCLAMATION);
		return NULL;
	}
	
	EGLDisplay glDisplay = eglGetDisplay(hdc);
	if (glDisplay == EGL_NO_DISPLAY)
		glDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);

	EGLint majorVerion;
	EGLint minorVerion;
	if (!eglInitialize(glDisplay, &majorVerion, &minorVerion))
	{
		MessageBox(NULL, "eglInitialize() failed", WINDOW_NAME, MB_OK | MB_ICONEXCLAMATION);
		ReleaseDC(hwnd, hdc);
		return NULL;
	}

	LOG("Initialized OPENGLES verion: %d.%d\n", majorVerion, minorVerion);
	
	*outHDC = hdc;

	return glDisplay;
}

EGLConfig static ConfigGLDisplay(EGLDisplay glDisplay)
{
	const EGLint pi32ConfigAttribs[] =
	{
		EGL_LEVEL,				0,
		EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
		EGL_NATIVE_RENDERABLE,	EGL_FALSE,		
		EGL_DEPTH_SIZE,			8,
		EGL_STENCIL_SIZE,		8,
		EGL_SAMPLE_BUFFERS,		1,
		EGL_NONE
	};

	EGLint configs;
	EGLConfig glConfig;
	EGLBoolean result = eglChooseConfig(glDisplay, pi32ConfigAttribs, &glConfig, 1, &configs);
	if (!result || configs != 1)
	{
		MessageBox(NULL, "eglChooseConfig() failed", WINDOW_NAME, MB_OK | MB_ICONEXCLAMATION);
		return NULL;
	}

	return glConfig;
}

bool static TestGLError(const char * funcName)
{
	EGLint error = eglGetError();
	if (error != EGL_SUCCESS)
	{
		char str[256];
		sprintf(str, "%s failed (%d).\n", funcName, error);
		MessageBox(NULL, str, WINDOW_NAME, MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}

EGLSurface static CreateGLSurface(EGLDisplay glDisplay, EGLConfig glConfig, EGLNativeWindowType glWindow)
{
	EGLSurface glSurface = eglCreateWindowSurface(glDisplay, glConfig, glWindow, NULL);
	if (glSurface == EGL_NO_SURFACE)
	{
		eglGetError();
		glSurface = eglCreateWindowSurface(glDisplay, glConfig, NULL, NULL);
	}

	bool success = TestGLError("eglCreateWindowSurface");
	return success ? glSurface : NULL;
}

EGLContext static BindGL(EGLDisplay glDisplay, EGLConfig glConfig, EGLSurface glSurface)
{
	eglBindAPI(EGL_OPENGL_ES_API);
	
	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	EGLContext glContext = eglCreateContext(glDisplay, glConfig, NULL, ai32ContextAttribs);
	if (!TestGLError("eglCreateContext"))
		return NULL;

	eglMakeCurrent(glDisplay, glSurface, glSurface, glContext);
	if (!TestGLError("eglMakeCurrent"))
		return NULL;

	return glContext;
}

LRESULT static CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT  lRet = 1; 
	int x = LOWORD(lparam); 
	int y = HIWORD(lparam);
	static bool mouseDown = false;

	switch (msg) 
	{ 
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break; 

	case WM_KEYDOWN:
		{
			if (context_tt.OnKey != 0)
			{
				context_tt.OnKey((int) wparam, true);
			}
		}		
		break;
	case WM_KEYUP:
		{
			if (context_tt.OnKey != 0)
			{
				context_tt.OnKey((int) wparam, false);
			}
		}
		break;
	case WM_LBUTTONDOWN:		
	case WM_RBUTTONDOWN:		
		mouseDown = true;		
		{
			if (context_tt.OnMouse != NULL)
			{
				context_tt.OnMouse(CONTROL_MOUSE_DOWN, x, y);
			}
		}
		break;

	case WM_LBUTTONUP:	
	case WM_RBUTTONUP:
		{
			mouseDown = false;
			if (context_tt.OnMouse != NULL)
			{
				context_tt.OnMouse(CONTROL_MOUSE_UP, x, y);
			}
		}
		break;
	case WM_MOUSEMOVE:		
		if (mouseDown)
		{			
			if (context_tt.OnMouse != NULL)
			{
				context_tt.OnMouse(CONTROL_MOUSE_MOVE, x, y);
			}
		}		
		break;
	default: 
		lRet = DefWindowProc (hwnd, msg, wparam, lparam); 
		break; 
	} 

	return lRet; 
}

/// implement functions

bool InitWindow(int width, int height)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	
	RegisterWindow(WndProc, hInstance);
	
	eglWindow = CreateGLWindow(width, height, hInstance);
	
	HDC hdc = NULL;
	eglDisplay = InitializeGLDisplay(eglWindow, &hdc);
	if (eglDisplay == NULL)
	{
		CleanWindow(eglDisplay, eglWindow, hdc);
		return false;
	}

	eglConfig = ConfigGLDisplay(eglDisplay);
	if (eglConfig == NULL)
	{
		CleanWindow(eglDisplay, eglWindow, hdc);
		return false;
	}

	eglSurface = CreateGLSurface(eglDisplay, eglConfig, eglWindow);
	if (eglSurface == NULL)
	{
		CleanWindow(eglDisplay, eglWindow, hdc);
		return false;
	}

	eglContext = BindGL(eglDisplay, eglConfig, eglSurface);
	if (eglContext == NULL)
	{
		CleanWindow(eglDisplay, eglWindow, hdc);
		return false;
	}

	return true;
}

void WinLoop()
{	
	MSG msg;
	memset(&msg, 0, sizeof(MSG));
	bool done = false;

	if (context_tt.OnInit)
		context_tt.OnInit();

	while (!done)
	{
		if  (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				done = true; 
			}
			else
			{
				TranslateMessage(&msg); 
				DispatchMessage(&msg); 
			}
		}

		if (context_tt.OnDraw)
			context_tt.OnDraw();

		if (context_tt.OnUpdate)
			context_tt.OnUpdate();

		eglSwapBuffers(eglDisplay, eglSurface);	
	}

	if (context_tt.OnDestroy)
		context_tt.OnDestroy();
}

void RegisterInitFunc(void (*OnInit)(void))
{
	context_tt.OnInit = OnInit;
}

void RegisterDestroyFunc(void (*OnDestroy)(void))
{
	context_tt.OnDestroy = OnDestroy;
}

void RegisterDrawFunc(void (*OnDraw)(void))
{
	context_tt.OnDraw = OnDraw;
}

void RegisterUpdateFunc(void (*OnUpdate)(void))
{
	context_tt.OnUpdate = OnUpdate;
}

void RegisterKeyFunc(void (*OnKey)(int, bool))
{
	context_tt.OnKey = OnKey;
}

void RegisterMouseFunc(void (*OnMouse)(int type, int x, int y))
{
	context_tt.OnMouse = OnMouse;
}

#endif