#pragma once
<<<<<<< Updated upstream
#include "IncludeLib.h"
using Microsoft::WRL::ComPtr; 
=======

#include "D3DApp.h"

// Environnement de d�bug de la Window
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <DirectXMath.h>
#include "D3DUtils.h"

// Liens n�cessaires de la librairie d3d12
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

using Microsoft::WRL::ComPtr;
using namespace DirectX;
>>>>>>> Stashed changes

class Renderer : D3DApp
{
public:
	Renderer();

};

<<<<<<< Updated upstream
=======
	HINSTANCE AppInst()const;
	HWND      MainWnd()const;
	float     AspectRatio()const;

	bool Get4xMsaaState()const;
	void Set4xMsaaState(bool value);

	int Run();

	virtual bool Initialize();
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


protected: // Fonctions prot�g�es

	bool InitMainWindow();

public: // Variables prot�g�es

	static Renderer* mApp;

	HINSTANCE mhAppInst = nullptr; // application instance handle
	HWND      mhMainWnd = nullptr; // main window handle
	bool      mAppPaused = false;  // is the application paused?
	bool      mMinimized = false;  // is the application minimized?
	bool      mMaximized = false;  // is the application maximized?
	bool      mResizing = false;   // are the resize bars being dragged?
	bool      mFullscreenState = false;// fullscreen enabled

	// Set true to use 4X MSAA (�4.1.8).  The default is false.
	bool      m4xMsaaState = false;    // 4X MSAA enabled
	UINT      m4xMsaaQuality = 0;      // quality level of 4X MSAA

	// 
	D3D12_VIEWPORT mScreenViewport;
	D3D12_RECT mScissorRect;

	// Dimension window
	int mClientWidth = 800;
	int mClientHeight = 600;
};
>>>>>>> Stashed changes
