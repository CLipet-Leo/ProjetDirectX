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

<<<<<<< HEAD
    // Camera creation (hard-coded)
    Params CamParams;
    std::vector<int> iLCamComp;
    iLCamComp.push_back(CAMERA);
    iLCamComp.push_back(CHARACTER_CONTROLLER);
    CamParams.cameraParams.theta = 1.5f * XM_PI;
    CamParams.cameraParams.phi = 0.2f * XM_PI;
    CamParams.cameraParams.radius = 15.0f;
    InstanciateEntity(iLCamComp, &CamParams);

    // Cube creation (hard-coded)
    Params CubeParams;
    std::vector<int> iLCubeComp;
    iLCubeComp.push_back(MESH_RENDERER);
    InstanciateEntity(iLCubeComp, &CubeParams);

=======
    Params params;
    std::vector<int> iLtypes;
    iLtypes.push_back(CHARACTER_CONTROLLER);
    iLtypes.push_back(MOVE);
    InstanciateEntity(iLtypes, &params);

    iLtypes.clear();
    iLtypes.push_back(MESH_RENDERER);

    InstanciateEntity(iLtypes, &params);
>>>>>>> 6728ab23a785fec586e8fc1729944db1885ca159

    //ScriptComponent* newScript;
    //params.LpScripts.push_back(newScript);


    return true;
}