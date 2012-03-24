#include "meshGen.h"


#pragma region Static Data

const D3D10_INPUT_ELEMENT_DESC MeshGen::inputLayoutArray[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
	{ "NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
//	,{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0},
};

#pragma endregion

MeshGen::MeshGen(void)
{
	fillMode = D3D10_FILL_SOLID;
}

MeshGen::~MeshGen(void)
{
}

void MeshGen::Init()
{
	BuildMesh();
}

SimpleVertex* MeshGen::GetVertexArray()
{
	return pVertexArray;
}

SimpleFace* MeshGen::GetFaceIndexArray()
{
	return pFaceIndexArray;
}

D3D10_INPUT_ELEMENT_DESC* MeshGen::GetInputLayoutArray()
{
	return (D3D10_INPUT_ELEMENT_DESC*)inputLayoutArray;
}

UINT MeshGen::VertexArrayByteWidth()
{
	return VertexArrayCount()*sizeof(SimpleVertex);
}

UINT MeshGen::VertexArrayCount()
{
	return aCount*bCount; // Number of vertices
}

UINT MeshGen::FaceIndexArrayByteWidth()
{
	return FaceCount()*sizeof(SimpleFace);
}

// Returns number of indexes in array
// Assumes all faces are triangles
UINT MeshGen::FaceIndexArrayCount()
{
	return FaceCount() * 3; 
}

UINT MeshGen::FaceCount()
{
	return faceCount;
}

UINT MeshGen::InputLayoutArrayByteWidth()
{
	return InputLayoutArrayCount()*sizeof(D3D10_INPUT_ELEMENT_DESC);
}

UINT MeshGen::InputLayoutArrayCount()
{
	return 2;
}

D3D10_FILL_MODE MeshGen::FillMode()
{
	return fillMode;
}

void MeshGen::BuildMesh()
{
}
