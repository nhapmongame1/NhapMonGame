#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include "DGraphic.h"
#include <stdio.h>
#include "Global.h"
#define APPTITLE L"Castle Vania"
RECT wr = { 0, 0, 640, 480 };
/*Window event callback function*/
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		/*Release the Direct3D device*/
		if (G_Device != NULL)
			G_Device->Release();
		/*Release the Direct3D object*/
		if (G_DirectX != NULL)
			G_DirectX->Release();
		/*Call the "Front-end" shutdown function*/
		Game_End(hWnd);
		/*Tell the windows to kill this program*/
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*Helper function to set up the window properties*/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	/*Fill the struct with info*/
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = APPTITLE;
	wc.lpszMenuName = NULL;

	/*Set up the window with the class info*/
	return RegisterClassEx(&wc);

}

/*Entry point for a Windows program*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hWnd;

	/*Register the class*/
	MyRegisterClass(hInstance);

	/*Set up the screen in windowed or fullscreen mode*/

	hWnd = CreateWindow(
		APPTITLE,
		APPTITLE,
		WS_OVERLAPPEDWINDOW,
		360,
		150,
		wr.right - wr.left,
		wr.bottom-wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	/*Was there an error creating the window*/
	if (!hWnd)
	{
		return FALSE;
	}

	/*Display the window*/
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (Init_Direct3D(hWnd, wr.right - wr.left, wr.bottom - wr.top, FULLSCREEN) == 0)
	{
		return 0;
	}

	/*Initialize the game*/
	if (!Game_Init(hWnd))
	{
		MessageBox(hWnd, L"Error initializing the game.", L"Error", MB_OK);
		return 0;
	}
	
	/*Main message loop*/
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/*Look for quit message*/
			if (msg.message == WM_QUIT)
				done = 1;
			/*Decode and pass message to the WndProc*/
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			/*Process game loop (prevents running after window is closed)*/
			Game_Run(hWnd);
	}
	return msg.wParam;
}
