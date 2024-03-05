#pragma once
#include"Mesh.h"
class MeshRenderer
{
public:

	MeshRenderer();
	~MeshRenderer();

	static void GetMeshesAndShaders(const std::string& name);
	//void DrawMeshesAndShaders(Mesh& mesh, Shader& shader);

};