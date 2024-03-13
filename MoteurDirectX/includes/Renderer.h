#pragma once
#include "Timer.h"
#include "MeshRenderer.h"
#include "Shader.h"
#include "Entity.h"
#include "../Components/CharacterController.h"

// Virtual Key define from Mathieu
#define VKm_Z		0x5A
#define VKm_Q		0x51
#define VKm_S		0x53
#define VKm_D		0x44
#define VKm_E		0x45

using namespace DirectX;

class Renderer
{
public:
	Renderer(HINSTANCE hInstance);
	Renderer(const Renderer& rhs) = delete;
	Renderer& operator=(const Renderer& rhs) = delete;
	virtual ~Renderer();

	static Renderer* GetApp();
	HWND MainWnd()const;

	float AspectRatio()const;

	void Set4xMsaaState(bool value);
	int Run();
	virtual bool Initialize();
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:

	virtual void CreateDescriptorHeaps();
	virtual void OnResize();
	virtual void Update(const Timer& gt);
	virtual void Draw(const Timer& gt);
	void InstanciateEntity(std::vector<int> compList, Params* params);

protected:

	bool InitMainWindow();
	bool InitDirect3D();
	void CreateDevice();
	void CreateFenceAndDescriptorSize();
	void Check4xMsaaQuality();
	void CreateCommandObjects();
	void CreateSwapChain();
	void CreateRenderTarget();
	void DepthStencilAndBufferView();
	void UpdateViewport();
	void FlushCommandQueue();
	void CalculateFrameStats();
	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

protected:
	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

public:
	/*----------------------------------------------------------------*/
	/*---------------------------GETTER-------------------------------*/
	/*----------------------------------------------------------------*/

	// Return the current back buffer
	ID3D12Resource* CurrentBackBuffer()const;
	// Return the CD3DX12_CPU_DESCRIPTOR_HANDLE current back buffer
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
	// Return _DsvHeap from GetCPUDescriptorHandleForHeapStart()
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;
	
	// Return the _d3dDevice.Get() variable
	Microsoft::WRL::ComPtr<ID3D12Device> CurrentDevice()const;
	// Return the _CommandQueue variable
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> GetCommandQueue()const;
	// Return the _CommandList variable
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CurrentCommandList()const;
	// Return the _DirectCmdListAlloc variable
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetCommandAlloc()const;

protected:

	static Renderer* _App;

	std::vector<Entity*> _LpEntity;
	std::vector<CharacterController*> _LpCharacterController;

	HINSTANCE hAppInst = nullptr; // application instance handle
	HWND hMainWnd = nullptr; // main window handle

	bool bAppPaused = false;  // is the application paused?
	bool bMinimized = false;  // is the application minimized?
	bool bMaximized = false;  // is the application maximized?
	bool bResizing = false;   // are the resize bars being dragged?

	Microsoft::WRL::ComPtr<IDXGIFactory4> _dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> _SwapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> _d3dDevice;

	Microsoft::WRL::ComPtr<ID3D12Fence> _Fence;
	UINT64 uCurrentFence = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> _CommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> _DirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _CommandList;

	static const int SwapChainBufferCount = 2;
	int iCurrBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> _SwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> _DepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _RtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _DsvHeap;

	D3D12_VIEWPORT _ScreenViewport;
	D3D12_RECT _ScissorRect;

	UINT uRtvDescriptorSize = 0;
	UINT uDsvDescriptorSize = 0;
	UINT uCbvSrvDescriptorSize = 0;

	bool b4xMsaaState = false;    // 4X MSAA enabled
	UINT u4xMsaaQuality = 0;      // quality level of 4X MSAA

	std::wstring sMainWndCaption = L"DirectX Engine";
	D3D_DRIVER_TYPE _d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	DXGI_FORMAT dBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT dDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;


	int iClientWidth = 800;
	int iClientHeight = 600;

	bool bFirstInit = true;

	Timer _Timer;
	MeshRenderer* meshRenderer;

	//XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT4X4 _m4World = MathHelper::Identity4x4();
	XMFLOAT4X4 _m4View = MathHelper::Identity4x4();
	XMFLOAT4X4 _m4Proj = MathHelper::Identity4x4();
	XMFLOAT4X4 _m4WorldViewProj = MathHelper::Identity4x4();
};
