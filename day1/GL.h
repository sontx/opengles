#pragma once
#include <stdio.h>
#include <gl2.h>
#include <windows.h>
#include <egl.h>

#if WIN32
#define CLASS_NAME			"www.sontx.in"
#define WINDOW_NAME			"www.sontx.in - opengles2.0"
#define LOG(fmt, ...)		{printf(fmt, __VA_ARGS__); printf("\n");}
#endif
#define MEM_FREE(p)			{if (p != NULL) {delete p; p = NULL;}}
#define MEM_FREE1D(p)		{if (p != NULL) {delete[] p; p = NULL;}}
#define CONTROL_MOUSE_DOWN	0
#define CONTROL_MOUSE_UP	1
#define CONTROL_MOUSE_MOVE	2