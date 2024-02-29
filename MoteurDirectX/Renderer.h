#pragma once
#include "Pch.h"

using namespace DirectX;

class Renderer
{
public:
	Renderer(int mClientWidth, int mClientHeight);

	void CreateDevice();
	void CreateFenceAndDescriptorSize();
	void Check4xMsaaQuality();
	void CreateCommandObjects();
	void CreateSwapChain(int mClientWidth, int mClientHeight);
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateRenderTarget();
	void DepthStencilAndBufferView(int mClientWidth, int mClientHeight);
	void CreateViewport(int mClientWidth, int mClientHeight);

public:

	HWND mhMainWnd = nullptr; // main window handle

	Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;

	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;

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

	DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

};
