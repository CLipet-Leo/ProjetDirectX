#include "includes/Pch.h"
#include "includes/Renderer.h"


using Microsoft::WRL::ComPtr;
using namespace std;
using namespace DirectX;

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before hMainWnd is valid.
	return Renderer::GetApp()->MsgProc(hwnd, msg, wParam, lParam);
}

Renderer* Renderer::_App = nullptr;
Renderer* Renderer::GetApp()
{
	return _App;
}

HWND Renderer::MainWnd()const
{
	return hMainWnd;
}

Renderer::Renderer(HINSTANCE hInstance)
	: hAppInst(hInstance)
{
	// Only one Renderer can be constructed.
	assert(_App == nullptr);
	_App = this;
}

Renderer::~Renderer()
{
	if (_d3dDevice != nullptr)
		FlushCommandQueue();
}

float Renderer::AspectRatio()const
{
	return static_cast<float>(iClientWidth) / iClientHeight;
}

void Renderer::Set4xMsaaState(bool value)
{
	if (b4xMsaaState != value)
	{
		b4xMsaaState = value;

		// Recreate the swapchain and buffers with new multisample settings.
		CreateSwapChain();
		OnResize();
	}
}

int Renderer::Run()
{

	char buff[200]{}; // Global within the class (in main.cpp, it's a member to avoid problems)

	MSG msg = { 0 };

	_Timer.Reset();

 
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
			_Timer.Update();

			if (!bAppPaused)
			{
				CalculateFrameStats();
				Update(_Timer);
				Draw(_Timer);
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

	// Reset the command list to prep for initialization commands.
	ThrowIfFailed(_CommandList->Reset(_DirectCmdListAlloc.Get(), nullptr));

	BuildDescriptorHeaps();
	BuildConstantBuffers();

	// Execute the initialization commands.
	ThrowIfFailed(_CommandList->Close());
	ID3D12CommandList* cmdsLists[] = { _CommandList.Get() };
	_CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	FlushCommandQueue();

	return true;
}

LRESULT Renderer::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			bAppPaused = true;
			_Timer.Pause();
		}
		else
		{
			bAppPaused = false;
			_Timer.Unpause();
		}
		return 0;

		// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
		// Save the new client area dimensions.
		iClientWidth = LOWORD(lParam);
		iClientHeight = HIWORD(lParam);
		if (_d3dDevice)
		{
			if (wParam == SIZE_MINIMIZED)
			{
				bAppPaused = true;
				bMinimized = true;
				bMaximized = false;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				bAppPaused = false;
				bMinimized = false;
				bMaximized = true;
				OnResize();
			}
			else if (wParam == SIZE_RESTORED)
			{

				// Restoring from minimized state?
				if (bMinimized)
				{
					bAppPaused = false;
					bMinimized = false;
					OnResize();
				}

				// Restoring from maximized state?
				else if (bMaximized)
				{
					bAppPaused = false;
					bMaximized = false;
					OnResize();
				}
				else if (bResizing)
				{
					// If user is dragging the resize bars, we do not resize 
					// the buffers here because as the user continuously 
					// drags the resize bars, a stream of WM_SIZE messages are
					// sent to the window, and it would be pointless (and slow)
					// to resize for each WM_SIZE message received from dragging
					// the resize bars.  So instead, we reset after the user is 
					// done resizing the window and releases the resize bars, which 
					// sends a WM_EXITSIZEMOVE message.
				}
				else // API call such as SetWindowPos or _SwapChain->SetFullscreenState.
				{
					OnResize();
				}
			}
		}
		return 0;

		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		bAppPaused = true;
		bResizing = true;
		_Timer.Pause();
		return 0;

		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		bAppPaused = false;
		bResizing = false;
		_Timer.Unpause();
		OnResize();
		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;

	case WM_LBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_KEYDOWN:

		if (wParam == VK_F2)
		{
			Set4xMsaaState(!b4xMsaaState);
		}

		for (auto curCharacterController : _LpCharacterController)
		{
			curCharacterController->Update(_Timer, wParam);
		}

		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Renderer::CreateDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = SwapChainBufferCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	ThrowIfFailed(_d3dDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(_RtvHeap.GetAddressOf())));

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	ThrowIfFailed(_d3dDevice->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(_DsvHeap.GetAddressOf())));
}

void Renderer::OnResize()
{
	assert(_d3dDevice);
	assert(_SwapChain);
	assert(_DirectCmdListAlloc);

	// Flush before changing any resources.
	FlushCommandQueue();

	ThrowIfFailed(_CommandList->Reset(_DirectCmdListAlloc.Get(), nullptr));

	// Release the previous resources we will be recreating.
	for (int i = 0; i < SwapChainBufferCount; ++i)
		_SwapChainBuffer[i].Reset();
	_DepthStencilBuffer.Reset();

	// Resize the swap chain.
	ThrowIfFailed(_SwapChain->ResizeBuffers(
		SwapChainBufferCount,
		iClientWidth, iClientHeight,
		dBackBufferFormat,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));

	iCurrBackBuffer = 0;

	CreateRenderTarget();

	DepthStencilAndBufferView();

	// Execute the resize commands.
	ThrowIfFailed(_CommandList->Close());
	ID3D12CommandList* cmdsLists[] = { _CommandList.Get() };
	_CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until resize is complete.
	FlushCommandQueue();

	UpdateViewport();

	// The window resized, so update the aspect ratio and recompute the projection matrix.
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);
}

void Renderer::Update(const Timer& gt)
{
	// update all Entities
	for (auto curEntity : _LpEntity)
	{
		curEntity->UpdateComponents(gt);
	}
}

void Renderer::Draw(const Timer& gt)
{
	// Reuse the memory associated with command recording.
	// We can only reset when the associated command lists have finished execution on the GPU.
	ThrowIfFailed(_DirectCmdListAlloc->Reset());

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
	// Reusing the command list reuses memory.
	if (_LpEntity.size() < 1)
	{
		ThrowIfFailed(_CommandList->Reset(_DirectCmdListAlloc.Get(), nullptr));
	}
	else
	{
		for (auto curEntity : _LpEntity)
		{
			curEntity->UpdateComponents(gt);
			MeshRenderer* curEntityModel = (MeshRenderer*)curEntity->GetComponentPtr(MESH_RENDERER);
			if (curEntityModel == nullptr)
			{
				ThrowIfFailed(_CommandList->Reset(_DirectCmdListAlloc.Get(), nullptr));
				continue;
			}
			ThrowIfFailed(_CommandList->Reset(_DirectCmdListAlloc.Get(), curEntityModel->GetPSO().Get()));
		}
	}

	_CommandList->RSSetViewports(1, &_ScreenViewport);
	_CommandList->RSSetScissorRects(1, &_ScissorRect);

	// Indicate a state transition on the resource usage.
	_CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	// Clear the back buffer and depth buffer.
	_CommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
	_CommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	// Specify the buffers we are going to render to.
	_CommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());
	//meshRenderer->RenderCube(_CommandList, CurrentBackBufferView(), DepthStencilView());

	// Indicate a state transition on the resource usage.
	_CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	// Done recording commands.
	ThrowIfFailed(_CommandList->Close());

	// Add the command list to the queue for execution.
	ID3D12CommandList* cmdsLists[] = { _CommandList.Get() };
	_CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// swap the back and front buffers
	ThrowIfFailed(_SwapChain->Present(0, 0));
	iCurrBackBuffer = (iCurrBackBuffer + 1) % SwapChainBufferCount;

	// Wait until frame commands are complete.  This waiting is inefficient and is
	// done for simplicity.  Later we will show how to organize our rendering code
	// so we do not have to wait per frame.
	FlushCommandQueue();
}

void Renderer::InstanciateEntity(std::vector<int> compList, Params* params)
{
	char buff[200]{};

	// puts the CharacterController component at the end of the list
	for (int i=0 ; i < compList.size() ; i++)
	{
		if (compList[i] == CHARACTER_CONTROLLER)
		{
			compList.erase(compList.begin() + i);
			compList.push_back(CHARACTER_CONTROLLER);
			break;
		}
	}

	Entity* newEntity = new Entity();

	for (auto curCompToAdd : compList)
	{
		Component* curNewComp = nullptr;

		switch (curCompToAdd)
		{
		case MOVE:
			curNewComp = new Move(newEntity, params);
			newEntity->AddComponent(curNewComp);
			break;
		case COLLIDER:
			break;
		case ROTATE:
			break;
		case GAME_OBJECT:
			curNewComp = new GameObject(newEntity, params);
			newEntity->AddComponent(curNewComp);
			break;
		case CHARACTER_CONTROLLER:
			CharacterController* newCC = new CharacterController(newEntity, params);
			newEntity->AddComponent(newCC);
			_LpCharacterController.push_back(newCC);
			break;
		}
	}

	_LpEntity.push_back(newEntity);
}

bool Renderer::InitMainWindow()
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hAppInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"MainWnd";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, iClientWidth, iClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	hMainWnd = CreateWindow(L"MainWnd", sMainWndCaption.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hAppInst, 0);
	if (!hMainWnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(hMainWnd, SW_SHOW);
	UpdateWindow(hMainWnd);

	return true;
}

bool Renderer::InitDirect3D()
{
	CreateDevice();

	CreateFenceAndDescriptorSize();

	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.

	Check4xMsaaQuality();

	#ifdef _DEBUG
	LogAdapters();
	#endif

	CreateCommandObjects();
	CreateSwapChain();
	CreateDescriptorHeaps();

	return true;
}


void Renderer::CreateDevice()
{
#if defined(DEBUG) || defined(_DEBUG)
// Enable the D3D12 debug layer.
{
	ComPtr<ID3D12Debug> debugController;
	ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
	debugController->EnableDebugLayer();
}
#endif
	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&_dxgiFactory)));
	// Try to create hardware device.
	HRESULT hardwareResult = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_d3dDevice));
	// Fallback to WARP device.
	if (FAILED(hardwareResult))
	{
		ComPtr<IDXGIAdapter> pWarpAdapter;
		ThrowIfFailed(_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)));
		ThrowIfFailed(D3D12CreateDevice(pWarpAdapter.Get(),D3D_FEATURE_LEVEL_11_0,IID_PPV_ARGS(&_d3dDevice)));
	}
}

void Renderer::CreateFenceAndDescriptorSize()
{
	ThrowIfFailed(_d3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_Fence)));
	uRtvDescriptorSize = _d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	uDsvDescriptorSize = _d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	uCbvSrvDescriptorSize = _d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void Renderer::Check4xMsaaQuality()
{
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
	msQualityLevels.Format = dBackBufferFormat;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;
	ThrowIfFailed(_d3dDevice->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msQualityLevels, sizeof(msQualityLevels)));
	u4xMsaaQuality = msQualityLevels.NumQualityLevels;
	assert(u4xMsaaQuality > 0 && "Unexpected MSAA quality level.");
}

void Renderer::CreateCommandObjects()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	ThrowIfFailed(_d3dDevice->CreateCommandQueue(
		&queueDesc, IID_PPV_ARGS(&_CommandQueue)));
	ThrowIfFailed(_d3dDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(_DirectCmdListAlloc.GetAddressOf())));
	ThrowIfFailed(_d3dDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		_DirectCmdListAlloc.Get(), // Associated command allocator
		nullptr, // Initial PipelineStateObject
		IID_PPV_ARGS(_CommandList.GetAddressOf())));
	// Start off in a closed state. This is because the first time we
	// refer to the command list we will Reset it, and it needs to be
	// closed before calling Reset.
	_CommandList->Close();
}

void Renderer::CreateSwapChain()
{
	// Release the previous swapchain we will be recreating.
	_SwapChain.Reset();
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = iClientWidth;
	sd.BufferDesc.Height = iClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = dBackBufferFormat;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = b4xMsaaState ? 4 : 1;
	sd.SampleDesc.Quality = b4xMsaaState ? (u4xMsaaQuality - 1) : 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = SwapChainBufferCount;
	sd.OutputWindow = hMainWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	// Note: Swap chain uses queue to perform flush.
	ThrowIfFailed(_dxgiFactory->CreateSwapChain(_CommandQueue.Get(), &sd, _SwapChain.GetAddressOf()));
}

void Renderer::CreateRenderTarget()
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(
		_RtvHeap->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < SwapChainBufferCount; i++)
	{
		// Get the ith buffer in the swap chain.
		ThrowIfFailed(_SwapChain->GetBuffer(
			i, IID_PPV_ARGS(&_SwapChainBuffer[i])));
		// Create an RTV to it.
		_d3dDevice->CreateRenderTargetView(
			_SwapChainBuffer[i].Get(), nullptr, rtvHeapHandle);
		// Next entry in heap.
		rtvHeapHandle.Offset(1, uRtvDescriptorSize);
	}
}

void Renderer::BuildDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
	cbvHeapDesc.NumDescriptors = 1;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.NodeMask = 0;
	ThrowIfFailed(_d3dDevice->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&_CbvHeap)));
}

void Renderer::BuildConstantBuffers()
{
	_ObjectCB = new UploadBuffer<ObjectConstants>(_d3dDevice, 1, true);

	UINT objCBByteSize = Utils::CalcConstantBufferByteSize(sizeof(ObjectConstants));

	D3D12_GPU_VIRTUAL_ADDRESS cbAddress = _ObjectCB->Resource()->GetGPUVirtualAddress();
	// Offset to the ith object constant buffer in the buffer.
	int boxCBufIndex = 0;
	cbAddress += boxCBufIndex * objCBByteSize;

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = cbAddress;
	cbvDesc.SizeInBytes = Utils::CalcConstantBufferByteSize(sizeof(ObjectConstants));

	_d3dDevice->CreateConstantBufferView(
		&cbvDesc,
		_CbvHeap->GetCPUDescriptorHandleForHeapStart());
}

void Renderer::DepthStencilAndBufferView()
{
	// Create the depth/stencil buffer and view.
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = iClientWidth;
	depthStencilDesc.Height = iClientHeight;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	depthStencilDesc.SampleDesc.Count = b4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = b4xMsaaState ? (u4xMsaaQuality - 1) : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = dDepthStencilFormat;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;
	ThrowIfFailed(_d3dDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		IID_PPV_ARGS(_DepthStencilBuffer.GetAddressOf())));

	// Create descriptor to mip level 0 of entire resource using the format of the resource.
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = dDepthStencilFormat;
	dsvDesc.Texture2D.MipSlice = 0;
	_d3dDevice->CreateDepthStencilView(_DepthStencilBuffer.Get(), &dsvDesc, DepthStencilView());

	// Transition the resource from its initial state to be used as a depth buffer.
	_CommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(_DepthStencilBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
}

void Renderer::UpdateViewport()
{
	// Update the viewport transform to cover the client area.
	_ScreenViewport.TopLeftX = 0;
	_ScreenViewport.TopLeftY = 0;
	_ScreenViewport.Width = static_cast<float>(iClientWidth);
	_ScreenViewport.Height = static_cast<float>(iClientHeight);
	_ScreenViewport.MinDepth = 0.0f;
	_ScreenViewport.MaxDepth = 1.0f;

	_ScissorRect = { 0, 0, iClientWidth, iClientHeight };
}

void Renderer::UpdateMainPassCB(const Timer& gt)
{
	XMMATRIX view = XMLoadFloat4x4(&mView);
	XMMATRIX proj = XMLoadFloat4x4(&mProj);

	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
	XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(view), view);
	XMMATRIX invProj = XMMatrixInverse(&XMMatrixDeterminant(proj), proj);
	XMMATRIX invViewProj = XMMatrixInverse(&XMMatrixDeterminant(viewProj), viewProj);

	XMStoreFloat4x4(&_MainPassCB.View, XMMatrixTranspose(view));
	XMStoreFloat4x4(&_MainPassCB.Proj, XMMatrixTranspose(proj));
	XMStoreFloat4x4(&_MainPassCB.ViewProj, XMMatrixTranspose(viewProj));
	_MainPassCB.EyePosW = mEyePos;
	_MainPassCB.RenderTargetSize = XMFLOAT2((float)iClientWidth, (float)iClientHeight);
	_MainPassCB.InvRenderTargetSize = XMFLOAT2(1.0f / iClientWidth, 1.0f / iClientHeight);
	_MainPassCB.NearZ = 1.0f;
	_MainPassCB.FarZ = 1000.0f;
	_MainPassCB.TotalTime = gt.getTotalTime();
	_MainPassCB.DeltaTime = gt.getDeltaTime();

	auto currPassCB = _PassCB;
	currPassCB->CopyData(0, _MainPassCB);
}


// Other utils functions

void Renderer::FlushCommandQueue()
{
	// Advance the fence value to mark commands up to this fence point.
	uCurrentFence++;

	// Add an instruction to the command queue to set a new fence point.  Because we 
	// are on the GPU timeline, the new fence point won't be set until the GPU finishes
	// processing all the commands prior to this Signal().
	ThrowIfFailed(_CommandQueue->Signal(_Fence.Get(), uCurrentFence));

	// Wait until the GPU has completed commands up to this fence point.
	if (_Fence->GetCompletedValue() < uCurrentFence)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);

		// Fire event when GPU hits current fence.  
		ThrowIfFailed(_Fence->SetEventOnCompletion(uCurrentFence, eventHandle));

		// Wait until the GPU hits current fence event is fired.
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}

void Renderer::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	// Compute averages over one second period.
	float fps = 1 / _Timer.getDeltaTime();
	float mspf = 1000.0f / fps;

	wstring fpsStr = to_wstring(fps);
	wstring mspfStr = to_wstring(mspf);

	wstring windowText = sMainWndCaption +
		L"    fps: " + fpsStr +
		L"   mspf: " + mspfStr;

	SetWindowText(hMainWnd, windowText.c_str());
}

void Renderer::LogAdapters()
{
	UINT i = 0;
	IDXGIAdapter* adapter = nullptr;
	std::vector<IDXGIAdapter*> adapterList;
	while (_dxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);

		std::wstring text = L"***Adapter: ";
		text += desc.Description;
		text += L"\n";

		OutputDebugString(text.c_str());

		adapterList.push_back(adapter);

		++i;
	}

	for (size_t i = 0; i < adapterList.size(); ++i)
	{
		LogAdapterOutputs(adapterList[i]);
		ReleaseCom(adapterList[i]);
	}
}

void Renderer::LogAdapterOutputs(IDXGIAdapter* adapter)
{
	UINT i = 0;
	IDXGIOutput* output = nullptr;
	while (adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_OUTPUT_DESC desc;
		output->GetDesc(&desc);

		std::wstring text = L"***Output: ";
		text += desc.DeviceName;
		text += L"\n";
		OutputDebugString(text.c_str());

		LogOutputDisplayModes(output, dBackBufferFormat);

		ReleaseCom(output);

		++i;
	}
}

void Renderer::LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format)
{
	UINT count = 0;
	UINT flags = 0;

	// Call with nullptr to get list count.
	output->GetDisplayModeList(format, flags, &count, nullptr);

	std::vector<DXGI_MODE_DESC> modeList(count);
	output->GetDisplayModeList(format, flags, &count, &modeList[0]);

	for (auto& x : modeList)
	{
		UINT n = x.RefreshRate.Numerator;
		UINT d = x.RefreshRate.Denominator;
		std::wstring text =
			L"Width = " + std::to_wstring(x.Width) + L" " +
			L"Height = " + std::to_wstring(x.Height) + L" " +
			L"Refresh = " + std::to_wstring(n) + L"/" + std::to_wstring(d) +
			L"\n";

		::OutputDebugString(text.c_str());
	}
}
/*----------------------------------------------------------------*/
/*---------------------------GETTER-------------------------------*/
/*----------------------------------------------------------------*/

ID3D12Resource* Renderer::CurrentBackBuffer()const
{
	return _SwapChainBuffer[iCurrBackBuffer].Get();
}

D3D12_CPU_DESCRIPTOR_HANDLE Renderer::CurrentBackBufferView()const
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		_RtvHeap->GetCPUDescriptorHandleForHeapStart(),
		iCurrBackBuffer,
		uRtvDescriptorSize);
}

D3D12_CPU_DESCRIPTOR_HANDLE Renderer::DepthStencilView()const
{
	return _DsvHeap->GetCPUDescriptorHandleForHeapStart();
}

ComPtr<ID3D12Device> Renderer::CurrentDevice()const
{
	return _d3dDevice;
}

ComPtr<ID3D12CommandQueue> Renderer::GetCommandQueue()const
{
	return _CommandQueue;
}

ComPtr<ID3D12GraphicsCommandList> Renderer::CurrentCommandList()const
{
	return _CommandList;
}

ComPtr<ID3D12CommandAllocator> Renderer::GetCommandAlloc()const
{
	return _DirectCmdListAlloc;
}