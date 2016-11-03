
#include "Global.h"



#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

//
//GLOBAL CONSTANT
//

// tieu nun
int G_CurForm;
// tieu nun
int G_NextForm;

bool		G_IsInitedDX = false;
int			G_GameDepth;
char*		G_GameName = "Sample TH";
int			G_FrameRate = 60;
int			G_ColorMode;
bool		G_IsFullScreen = false;
D3DFORMAT	G_BackBufferFormat;

bool		G_HasBackgroundSound = true;
bool		G_HasEffectSound = true;

int			G_MapWidth;
int			G_MapHeight;

int			G_MaxSize;
int			G_MinSize;

RECT		G_WindowSize;
int			G_ScreenWidth = 515; //640;	//640	//1024	//1366
int			G_ScreenHeight = 450; //480;	//480	//768	//768

//
//GLOBAL VARIANT
//

HINSTANCE					G_hInstance;		// Handle of the game instance
HWND						G_hWnd;				// Handle of the Game Window

LPDIRECT3D9					G_DirectX;
LPDIRECT3DDEVICE9			G_Device;
LPDIRECT3DSURFACE9			G_BackBuffer;

LPDIRECTINPUT8				G_DirectInput;		// The DirectInput object         
LPDIRECTINPUTDEVICE8		G_KeyBoard;			// The keyboard device 
LPD3DXSPRITE				G_SpriteHandler;	// spriteHandler to draw texture

