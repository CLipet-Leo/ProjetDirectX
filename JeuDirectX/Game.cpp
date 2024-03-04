/*
     ///                  !! WARNING !!                   \\\
    | This file has the  Game class AND the WinMain function |
    |              It is NOT only a class file               |
     \\\                  !! WARNING !!                   ///
*/

#include <Pch.h>
#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
    PSTR cmdLine, int showCmd)
{
#ifdef _DEBUG
    _CrtMemState memStateInit;
    _CrtMemCheckpoint(&memStateInit);
#endif

    try
    {
        Game theApp(hInstance);
        if (!theApp.Initialize())
            return 0;
    
        return theApp.Run();
    }
    catch (DxException& e)
    {
        MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
        return 0;
    }

#ifdef _DEBUG
    _CrtMemState memStateEnd, memStateDiff;
    _CrtMemCheckpoint(&memStateEnd);
    if (_CrtMemDifference(&memStateDiff, &memStateInit, &memStateEnd))
    {
        MessageBoxA(NULL, "MEMORY LEAKS", "DISCLAIMER", 0);
    }
#endif 

    return 0;
}


Game::Game(HINSTANCE hInstance)
    : Renderer(hInstance)
{
    /**/ /* <[)  BAPT CODE :3  (]> */ /**/
    // Yes I know I could've done ": variable(value)", but it UGLEH
    _pM4World = &(MathHelper::Identity4x4());
    _pM4View = &(MathHelper::Identity4x4());
    _pM4Proj = &(MathHelper::Identity4x4());
    /**/ /* <[)  BAPT CODE :3  (]> */ /**/
}

Game::~Game()
{
    if (md3dDevice != nullptr)
        FlushCommandQueue();
}

bool Game::Initialize()
{
    if (!Renderer::Initialize())
        return false;

    return true;
}

void Game::OnResize()
{
    Renderer::OnResize();
}


void Game::Update(const Timer& gt)
{

}

void Game::Draw(const Timer& gt)
{
    // Reuse the memory associated with command recording.
    // We can only reset when the associated command lists have finished
    // execution on the GPU.
    ThrowIfFailed(mDirectCmdListAlloc->Reset());
    // A command list can be reset after it has been added to the
    // command queue via ExecuteCommandList. Reusing the command list reuses memory.
    ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));
    // Indicate a state transition on the resource usage. [BAPT : Swap the two Buffers in the SwapChain]
    mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
    // Set the viewport and scissor rect. This needs to be reset
    // whenever the command list is reset.
    mCommandList->RSSetViewports(1, &mScreenViewport);
    mCommandList->RSSetScissorRects(1, &mScissorRect);
    // Clear the back buffer and depth buffer.
    mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
    mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
    // Specify the buffers we are going to render to.
    mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());
    // Indicate a state transition on the resource usage.
    mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
    // Done recording commands.
    ThrowIfFailed(mCommandList->Close());
    // Add the command list to the queue for execution.
    ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
    mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
    // swap the back and front buffers
    ThrowIfFailed(mSwapChain->Present(0, 0));
    mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;
    // Wait until frame commands are complete. This waiting is
    // inefficient and is done for simplicity. Later we will show how to
    // organize our rendering code so we do not have to wait per frame.
    FlushCommandQueue();
}