#include<Windows.h>
#include<gl/GL.h>
#include<math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

#pragma comment(lib,"opengl32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool gbFullscreen = false;
bool gbActiveWindow = false;
bool gbEscPressed = false;

HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

WINDOWPLACEMENT wpPrev;
DWORD dwStyle;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	void initialize();
	void uninitialize();
	void display();

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");
	bool bDone = false;

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("My Window"),
		WS_OVERLAPPEDWINDOW,
		GetSystemMetrics(SM_CXSCREEN) / 2 - 400,
		GetSystemMetrics(SM_CYSCREEN) / 2 - 400,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	initialize();

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = true;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == true)
			{
				display();
				if (gbEscPressed == true)
					bDone = true;
			}
		}
	}

	uninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void resize(int, int);
	void uninitialize();
	void ToggleFullscreen();

	switch (iMsg)
	{
	case WM_ACTIVATE:
		if (HIWORD(wParam) == 0)
			gbActiveWindow = true;
		else
			gbActiveWindow = false;
		break;
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			gbEscPressed = true;
			break;
		case 0x46:
			if (gbFullscreen == false)
			{
				ToggleFullscreen();
				gbFullscreen = true;
			}
			else
			{
				ToggleFullscreen();
				gbFullscreen = false;
			}
			break;
		default:
			break;
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}

void ToggleFullscreen(void)
{
	MONITORINFO mi;

	if (gbFullscreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi = { sizeof(MONITORINFO) };
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}

void initialize()
{
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	ghdc = GetDC(ghwnd);

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelFormatIndex == 0)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;

		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//resize(WIN_WIDTH, WIN_HEIGHT);
}

void display()
{
	void Deathly_hollows(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Deathly_hollows(0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f);

	SwapBuffers(ghdc);
}

void Deathly_hollows(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3)
{
	GLfloat a, b, c, k, r, cx, cy, xm, ym;
	GLint circle_points = 100;
	const GLfloat pi = 3.14f;
	GLfloat rad = 0.1f, angle;

	// Sides of triangle
	a = sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));
	b = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
	c = sqrt(pow((x2 - x3), 2) + pow((y2 - y3), 2));

	k = (a + b + c) / 2;
	r = sqrt((k*(k - a)*(k - b)*(k - c))) / k;

	xm = (x2 + x3) / 2; //X co-ordinate of median
	ym = (y2 + y3) / 2; //Y co-ordinate of median

	//Incenter co-ordinates
	cx = xm;
	cy = ym + r;

	glBegin(GL_LINE_LOOP);
	glVertex3f(x1, y1, 0.0f);
	glVertex3f(x2, y2, 0.0f);
	glVertex3f(x3, y3, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(x1, y1, 0.0f);
	glVertex3f(xm, ym, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int j = 0;j < circle_points; j++)
	{
		angle = 2 * pi * j / circle_points;
		glVertex3f(cx + cos(angle)*r, cy + sin(angle)*r, 0.0f);
	}
	glEnd();
}
void resize(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void uninitialize(void)
{
	if (gbFullscreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}

	wglMakeCurrent(NULL, NULL);

	wglDeleteContext(ghrc);
	ghrc = NULL;

	ReleaseDC(ghwnd, ghdc);
	ghdc = NULL;

	DestroyWindow(ghwnd);
	ghwnd = NULL;
}