#pragma once

#include <d3d10.h>
#include <D3DX10math.h>

/******************************************************************
*                                                                 *
*  Structs                                                        *
*                                                                 *
******************************************************************/

typedef struct SimpleVertex
{
    D3DXVECTOR3 Pos;
	D3DXVECTOR3 N;
} SimpleVertex;

typedef struct SimpleFace
{
	//SHORT vIdx[3];
	SHORT v0;
	SHORT v1;
	SHORT v2;
} SimpleFace;


class MeshGen
{
public:
	MeshGen(void);
	virtual ~MeshGen(void);

	void Init();

	SimpleVertex* GetVertexArray();
	SimpleFace* GetFaceIndexArray();
	D3D10_INPUT_ELEMENT_DESC* GetInputLayoutArray();

	UINT VertexArrayByteWidth();
	UINT VertexArrayCount();

	UINT FaceIndexArrayByteWidth();
	UINT FaceIndexArrayCount();
	UINT FaceCount();

	UINT InputLayoutArrayByteWidth();
	UINT InputLayoutArrayCount();

	D3D10_FILL_MODE FillMode();

protected:
	UINT faceCount;

	SimpleVertex* pVertexArray;
	SimpleFace* pFaceIndexArray;

	static const D3D10_INPUT_ELEMENT_DESC inputLayoutArray[];

	// Sphere
	//UINT aCount = 360;
	//UINT bCount = 360;

	// Cube
	SHORT aCount;
	SHORT bCount;

	D3D10_FILL_MODE fillMode;

protected:
	virtual void BuildMesh();
};

