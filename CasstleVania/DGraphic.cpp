#include <d3d9.h>
#include <d3dx9.h>
#include "DGraphic.h"
#include "Global.h"
			 
/*Variable declarations*/
int Init_Direct3D(HWND hWnd, int width, int height, int fullscreen)
{
	/*Initialize Direct3D*/
	G_DirectX = Direct3DCreate9(D3D_SDK_VERSION);
	if (G_DirectX == NULL)
	{
		MessageBox(hWnd, L"Error initializing Direct3D", L"Error", MB_OK);
		return 0;
	}

	/*Set Direct3D present parameters*/
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferWidth = width;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	/*Create Device*/
	G_DirectX->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&G_Device);

	if (G_Device == NULL)
	{
		MessageBox(hWnd, L"Error creating Direct3D Device", L"Error", MB_OK);
		return 0;
	}

	G_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	/*Create pointer to the backbuffer*/
	G_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &G_BackBuffer);

	return 1;
}

LPDIRECT3DSURFACE9 LoadSurface(char* filename, D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;

	/*Get width and height from bitmapp file*/
	result = D3DXGetImageInfoFromFileA(filename, &info);

	if (result != NULL)
	{
		return NULL;
	}
	/*Create surface*/
	result = G_Device->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&image,
		NULL);

	if (result != NULL)
	{
		return NULL;
	}

	/*Load surface from file into newly created surface*/
	result = D3DXLoadSurfaceFromFile(
		image,
		NULL,
		NULL,
		(wchar_t*)filename,
		NULL,
		D3DX_DEFAULT,
		transcolor,
		NULL);

	/*Make sure file was loaded okay */
	if (result!=NULL)
	{
		return NULL;
	}
	return image;
}
LPDIRECT3DTEXTURE9 LoadTexture(char *filename, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;

	D3DXIMAGE_INFO info;

	/*standard Windows return value*/
	HRESULT result;

	result = D3DXGetImageInfoFromFileA(filename, &info);
	if (result != D3D_OK)
		return NULL;

	D3DXCreateTextureFromFileExA(
		G_Device,
		filename,
		info.Width,
		info.Height,
		1,								//mip-map levels (1 for no chain)
		D3DPOOL_DEFAULT,				//the type of surface (standard)
		D3DFMT_UNKNOWN,					//surface format (default)
		D3DPOOL_DEFAULT,				//memory class for the texture
		D3DX_DEFAULT,					//image filter
		D3DX_DEFAULT,					//mip filter
		transcolor,
		&info,
		NULL,							//color palette
		&texture);						 //destination texture
	if (result != D3D_OK)
		return NULL;
	return texture;
}
D3DXIMAGE_INFO GetInfo(char *filename)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFileA(filename, &info);
	return info;
}