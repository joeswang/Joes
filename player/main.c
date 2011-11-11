#include <windows.h>
#include "resource.h"

// Global Variables:
HINSTANCE	g_hInstance;							// current instance
HDC			g_memdc;
HBITMAP		g_hbit;
HBRUSH		g_hbrush;
int maxX, maxY;

char szTitle[] = ("MBoo Player");				// The title bar text
char szWindowClass[] = ("MBoo.Player");			// the main window class name

// Forward declarations of functions included in this code module:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
WNDCLASSEX wcex;
HWND hWnd = NULL;
MSG msg;

	g_hInstance = hInstance; // Store instance handle in our global variable
	//UNREFERENCED_PARAMETER(hPrevInstance);
	//UNREFERENCED_PARAMETER(lpCmdLine);

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDM_MAIN);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON_SMALL));

	RegisterClassEx(&wcex);

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}


////////////////////////////////////////////////////////
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
int i, x, y;
int wmId, wmEvent;
PAINTSTRUCT ps;
TEXTMETRIC	tm;
char str[255];
HDC hdc;
int l,t,b,r;

	switch (message)
	{
	case WM_CREATE:
		maxX = GetSystemMetrics(SM_CXSCREEN);
		maxY = GetSystemMetrics(SM_CYSCREEN);
		hdc = GetDC(hWnd);
		g_memdc = CreateCompatibleDC(hdc);
		g_hbit  = CreateCompatibleBitmap(hdc, maxX, maxY);
		SelectObject(g_memdc, g_hbit);
		g_hbrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
		SelectObject(g_memdc, g_hbrush);
		PatBlt(g_memdc, 0, 0, maxX, maxY, PATCOPY);

		GetTextMetrics(hdc, &tm);
		x = 10; y = 0;
		for(i=0; i<24; i++)
		{
			strcpy(str, "Using a virtual window");
			TextOut(g_memdc, x, y, str, strlen(str));

			y += (tm.tmHeight + tm.tmExternalLeading);
		}
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, 0);
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		l = ps.rcPaint.left; t = ps.rcPaint.top; r = ps.rcPaint.right; b = ps.rcPaint.bottom;
		BitBlt(hdc, l, t, r-l, b-t, g_memdc, l, t, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteDC(g_memdc);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
