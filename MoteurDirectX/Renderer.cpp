#include "Renderer.h"
#include <WindowsX.h>
#include <string>
#include <vector>

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return Renderer::GetApp()->MsgProc(hwnd, msg, wParam, lParam);
}

Renderer* Renderer::mApp = nullptr;
Renderer* Renderer::GetApp()
{
	return mApp;
}

Renderer::Renderer(HINSTANCE hInstance)
	: mhAppInst(hInstance)
{
	// Only one Renderer can be constructed.
	assert(mApp == nullptr);
	mApp = this;
}

Renderer::~Renderer()
{
	if (d3d_app.md3dDevice != nullptr)
		d3d_app.FlushCommandQueue();
}

HINSTANCE Renderer::AppInst()const
{
	return mhAppInst;
}

HWND Renderer::MainWnd()const
{
	return mhMainWnd;
}

float Renderer::AspectRatio()const
{
	return static_cast<float>(mClientWidth) / mClientHeight;
}

bool Renderer::Get4xMsaaState()const
{
	return m4xMsaaState;
}

void Renderer::Set4xMsaaState(bool value)
{
	if (m4xMsaaState != value)
	{
		m4xMsaaState = value;

		// Recreate the swapchain and buffers with new multisample settings.
		d3d_app.CreateSwapChain();
		d3d_app.OnResize();
	}
}

int Renderer::Run()
{
	MSG msg = { 0 };

	//mTimer.Reset();

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else
		{
			//mTimer.Tick();

			if (!mAppPaused)
			{
				//CalculateFrameStats();
				//Update(mTimer);
				//Draw(mTimer);
			}
			else
			{
				Sleep(100);
			}
		}
	}

	return (int)msg.wParam;
}

bool Renderer::Initialize()
{
	if (!InitMainWindow())
		return false;

	if (!d3d_app.InitDirect3D())
		return false;

	// Do the initial resize code.
	d3d_app.OnResize();

	return true;
}

bool Renderer::InitMainWindow()
{
	return false;
}
