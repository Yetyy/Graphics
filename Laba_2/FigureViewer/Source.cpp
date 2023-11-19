#pragma once
#include <Windows.h>
#include <windowsx.h>

#include "Render2D.h"
#include "AffineTransform.h"

# define M_PI 3.14159265358979323846

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure);
LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

Render2D render;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

	render.addObject(new Model2D("pentagon.txt", 100, 0));
	render.addObject(new Model2D("sc.txt", 100, 0));

	WNDCLASS mainWindow = createWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", windowProcedure);

	if (!RegisterClass(&mainWindow))
		return -1;

	CreateWindow(LPCSTR(L"MainWndClass"), LPCSTR(L"MainWindow"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 800, NULL, NULL, NULL, NULL);

	MSG message = { 0 };
	while (GetMessage(&message, NULL, NULL, NULL)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure)
{
	WNDCLASS wc = { 0 };

	wc.hCursor = cursor;
	wc.hIcon = icon;
	wc.hInstance = hInstance;
	wc.lpszClassName = LPCSTR(windowName);
	wc.hbrBackground = bgColor;
	wc.lpfnWndProc = windowProcedure;

	return wc;
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc = NULL;
	HBRUSH brush = NULL;
	const char KEY_W = 0x57;
	const char KEY_Q = 0x51;
	const char KEY_E = 0x45;
	const char KEY_S = 0x53;
	const char KEY_C = 0x43;

	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = GetDC(hWnd);
		brush = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(hdc, brush);
		render.draw(hdc);
		DeleteObject(brush);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_MOUSEWHEEL:
	{
		double wheelNow = GET_WHEEL_DELTA_WPARAM(wp);

		if (wheelNow > 0) {
			render.applyToObj(Scaling(1.1, 1.1));
		}
		else {
			render.applyToObj(Scaling(0.9, 0.9));
		}

		InvalidateRect(hWnd, nullptr, true);
	}
	case WM_KEYDOWN:
	{
		switch (wp)
		{
		case VK_UP:
		{
			render.get_model()->Translation_M(0, -10);
			break;
		}
		case VK_DOWN:
		{
			render.get_model()->Translation_M(0, 10);
			break;
		}
		case VK_LEFT:
		{
			render.get_model()->Translation_M(-10, 0);
			break;
		}
		case VK_RIGHT:
		{
			render.get_model()->Translation_M(10, 0);
			break;
		}
		case KEY_W:
		{
			render.applyToObj(ReflectOY());
			break;
		}
		case KEY_S:
		{
			render.applyToObj(ReflectOX());
			break;
		}
		case KEY_Q:
		{
			render.get_model()->Rotation_M(-45);
			//render.applyToObj(Rotation( M_PI/ 4));
			break;
		}
		case KEY_E:
		{
			render.get_model()->Rotation_M(45);
			//render.applyToObj(Rotation(M_PI / 4));
			break;
		}
		case KEY_C:
		{
			render.nextObj();
			break;
		}
		}
		InvalidateRect(hWnd, NULL, true);
		return 0;
	}
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}
