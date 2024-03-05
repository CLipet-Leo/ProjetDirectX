#include "includes/Pch.h"
#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::GetMeshesAndShaders(const std::string& name)
{
	// Recupere les meshes et les shaders 
	Mesh* mesh;
	Shader* shader;

	mesh->GetMesh(name);
	shader->GetShader();
	// Getsubmesh 
}

void MeshRenderer::DrawMeshesAndShaders(Mesh& mesh, Shader& shader) {

}