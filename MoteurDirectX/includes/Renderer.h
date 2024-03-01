#pragma once
#include "Timer.h"


using namespace DirectX;

class Renderer
{
public:
	Renderer(HINSTANCE hInstance);
	Renderer(const Renderer& rhs) = delete;
	Renderer& operator=(const Renderer& rhs) = delete;
	virtual ~Renderer();

	static Renderer* GetApp();

	void Set4xMsaaState(bool value);
	int Run();

	virtual bool Initialize();
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	virtual void Update(const Timer& gt)=0;
	virtual void Draw(const Timer& gt)=0;

protected:

	bool InitMainWindow();
	bool InitDirect3D();
	void CreateDevice();
	void CreateFenceAndDescriptorSize();
	void Check4xMsaaQuality();
	void CreateCommandObjects();
	void CreateSwapChain();
	void CreateDescriptorHeaps();
	void CreateRenderTarget();
	void DepthStencilAndBufferView();
	void CreateViewport();
	void FlushCommandQueue();

	ID3D12Resource* CurrentBackBuffer()const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;

protected:
	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

protected:
	Timer mTimer;

	static Renderer* mApp;

	HINSTANCE mhAppInst = nullptr; // application instance handle
	HWND mhMainWnd = nullptr; // main window handle

	bool mAppPaused = false;  // is the application paused?
	bool mMinimized = false;  // is the application minimized?
	bool mMaximized = false;  // is the application maximized?
	bool mResizing = false;   // are the resize bars being dragged?

	Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;

	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
	UINT64 mCurrentFence = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;

	static const int SwapChainBufferCount = 2;
	int mCurrBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;

	D3D12_VIEWPORT mScreenViewport;
	D3D12_RECT mScissorRect;

	UINT mRtvDescriptorSize = 0;
	UINT mDsvDescriptorSize = 0;
	UINT mCbvSrvDescriptorSize = 0;

	bool m4xMsaaState = false;    // 4X MSAA enabled
	UINT m4xMsaaQuality = 0;      // quality level of 4X MSAA

	std::wstring mMainWndCaption = L"d3d App";
	DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	int mClientWidth = 800;
	int mClientHeight = 800;

};
