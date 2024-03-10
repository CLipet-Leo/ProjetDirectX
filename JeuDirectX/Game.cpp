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

    char buff[200]{}; // Global within the class (in main.cpp, it's a member to avoid problems)

    try
    {
        Game theApp(hInstance);
        if (!theApp.Initialize())
            return 0;
    
        printf("hello");
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
    if (_d3dDevice != nullptr)
        FlushCommandQueue();
}

bool Game::Initialize()
{
    if (!Renderer::Initialize())
        return false;

    Params params;

    std::vector<int> iLtypes;

    iLtypes.push_back(CHARACTER_CONTROLLER);
    iLtypes.push_back(MOVE);

    InstanciateEntity(iLtypes, &params);

    return true;
}