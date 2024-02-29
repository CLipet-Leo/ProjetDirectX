#pragma once

// Environnement de débug de la Window
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <windows.h>
#include <WindowsX.h>
#include <WinBase.h>
#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
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
#include "..\DirectX\d3dx12.h"
#include "..\DirectX\DDSTextureLoader.h"
#include "..\DirectX\MathHelper.h"
#include "CustomVertex.h"
#include "Renderer.h"
#include "D3DUtils.h"
#include "Shader.h"
#include "Timer.h"


// Liens nécessaires de la librairie d3d12
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")