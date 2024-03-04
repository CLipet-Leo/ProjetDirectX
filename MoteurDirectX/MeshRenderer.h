#pragma once
class MeshRenderer
{
public:

	MeshRenderer();
	~MeshRenderer();

	static void GetMeshesAndShaders(const std::string& name);
	void DrawMeshesAndShaders(Mesh& mesh, Shader& shader);

};