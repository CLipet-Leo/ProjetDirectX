#pragma once


// Environnement de débug de la Window
#if defined(DEBUG) || defined(_DEBUG)
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

// Windows libs
#include <windows.h>
#include <WindowsX.h>
#include <WinBase.h>
#include <wrl.h>

// Stuff to print in the Visual console
#include <stdio.h>
#define VSCPrint(buffer, msg, ...) \
    do{ \
        _snprintf_s(buffer, sizeof(buffer), _TRUNCATE, msg, __VA_ARGS__); \
        OutputDebugStringA(buffer); \
    } while(0)

// DirectX libs
#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

// C++ Standard libs
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <cassert>
#include <comdef.h>
#include <locale>
#include <codecvt>


// Enum
enum compSubType
{
	UNKNOWN = 0,
	CAMERA,
	COLLIDER,
	FACTORY,
	ROTATE,
	MOVE,
	PARTICLE_GEN,
	GAME_OBJECT,
	CHARACTER_CONTROLLER,
};

// More DirectX libs
#include "..\..\DirectX\d3dx12.h"
#include "..\..\DirectX\DDSTextureLoader.h"
#include "..\..\DirectX\MathHelper.h"

// Custom code libs
#include "..\..\DirectX\UploadBuffer.h"
#include "CustomVertex.h"
#include "Mesh.h"
#include "Shader.h"
#include "Renderer.h"
#include "Utils.h"
#include "MeshRenderer.h"
#include "Timer.h"
#include "Transform.h"
// TODO move headers in include folder
#include "Component.h"
#include "Entity.h"
#include "../Components/GameObject.h"
#include "../Components/Move.h"
#include "../Components/CharacterController.h"
// TODO
//#include "Collider.h"
//#include "Rotate.h"

// Liens nécessaires de la librairie d3d12
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")