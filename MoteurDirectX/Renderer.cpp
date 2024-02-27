#include "Renderer.h"

Renderer::Renderer()
{

}

<<<<<<< Updated upstream
//int main()
//{
//	std::cout << "JE FUIS !!!" << std::endl;
//	return 0;
//}
=======
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
	if (md3dDevice != nullptr)
		FlushCommandQueue();
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
		CreateSwapChain();
		OnResize();
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

	if (!InitDirect3D())
		return false;

	// Do the initial resize code.
	OnResize();

	return true;
}

bool Renderer::InitMainWindow()
{
	return false;
}
>>>>>>> Stashed changes
