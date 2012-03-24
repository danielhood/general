#include "CubeMesh.h"

#pragma region Static Arrays

#pragma region Old Data
/*
const SimpleVertex s_VertexArray[] =
{
	{ D3DXVECTOR3( -1.0f, -1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) }, 
	{ D3DXVECTOR3(  1.0f, -1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) }, 
	{ D3DXVECTOR3(  1.0f,  1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) }, 
	{ D3DXVECTOR3( -1.0f,  1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) }
};

const SHORT s_FacesIndexArray[] =
{
	3, 1, 0,
	2, 1, 3
};
*/

/*
const SimpleVertex s_VertexArray[] =
{
	{ D3DXVECTOR3(  1.0f,  1.0f, 1.0f ), D3DXVECTOR3( 1.0f, 0.0f, 0.0f ) }, 
	{ D3DXVECTOR3(  1.0f, -1.0f, 1.0f ), D3DXVECTOR3( 1.0f, 0.0f, 0.0f ) }, 
	{ D3DXVECTOR3( -1.0f, -1.0f, 1.0f ), D3DXVECTOR3( 1.0f, 0.0f, 0.0f ) }
};

const SHORT s_FacesIndexArray[] =
{
	2,1,0
};
*/



//const SimpleVertex s_VertexArray[] =
//{
//	{ D3DXVECTOR3( -1.0f, -1.0f, 1.0f ),  D3DXVECTOR3(-1.0f, 0.0f, 0.0f )  }, 
//	{ D3DXVECTOR3(  1.0f, -1.0f, 1.0f ),  D3DXVECTOR3(-1.0f, 0.0f, 0.0f )  }, 
//	{ D3DXVECTOR3(  1.0f,  1.0f, 1.0f ),  D3DXVECTOR3(-1.0f, 0.0f, 0.0f )  }, 
//	{ D3DXVECTOR3( -1.0f,  1.0f, 1.0f ),  D3DXVECTOR3(-1.0f, 0.0f, 0.0f )  },
//	{ D3DXVECTOR3( -1.0f, -1.0f, -1.0f ), D3DXVECTOR3(-1.0f, 0.0f, 0.0f )  }, 
//	{ D3DXVECTOR3(  1.0f, -1.0f, -1.0f ), D3DXVECTOR3(-1.0f, 0.0f, 0.0f )  }, 
//	{ D3DXVECTOR3(  1.0f,  1.0f, -1.0f ), D3DXVECTOR3(-1.0f, 0.0f, 0.0f )  }, 
//	{ D3DXVECTOR3( -1.0f,  1.0f, -1.0f ), D3DXVECTOR3(-1.0f, 0.0f, 0.0f )  }
//};

#pragma endregion

const SimpleVertex CubeMesh::vertexArray[] =
{
	{ D3DXVECTOR3( -1.0f, -1.0f, 1.0f ),  D3DXVECTOR3(-1.0f, -1.0f, 1.0f )  }, 
	{ D3DXVECTOR3(  1.0f, -1.0f, 1.0f ),  D3DXVECTOR3( 1.0f, -1.0f, 1.0f )  }, 
	{ D3DXVECTOR3(  1.0f,  1.0f, 1.0f ),  D3DXVECTOR3( 1.0f,  1.0f, 1.0f )  }, 
	{ D3DXVECTOR3( -1.0f,  1.0f, 1.0f ),  D3DXVECTOR3(-1.0f,  1.0f, 1.0f )  },
	{ D3DXVECTOR3( -1.0f, -1.0f, -1.0f ), D3DXVECTOR3( -1.0f, -1.0f, -1.0f ) }, 
	{ D3DXVECTOR3(  1.0f, -1.0f, -1.0f ), D3DXVECTOR3( 1.0f, -1.0f, -1.0f ) }, 
	{ D3DXVECTOR3(  1.0f,  1.0f, -1.0f ), D3DXVECTOR3( 1.0f,  1.0f, -1.0f ) }, 
	{ D3DXVECTOR3( -1.0f,  1.0f, -1.0f ), D3DXVECTOR3(-1.0f,  1.0f, -1.0f ) }
};

const SHORT CubeMesh::facesIndexArray[] =
{
	3, 1, 0,
	2, 1, 3,

	2, 5, 1,
	6, 5, 2,

	6, 4, 5,
	7, 4, 6,

	7, 0, 4,
	3, 0, 7,

	7, 2, 3,
	6, 2, 7,

	5, 4, 1,
	4, 0, 1,
};

#pragma endregion

CubeMesh::CubeMesh(void) : MeshGen()
{
	// Cube
	aCount = 2;
	bCount = 4;
	faceCount = aCount*bCount+aCount*bCount/2;
}

CubeMesh::~CubeMesh(void)
{
}

void CubeMesh::BuildMesh()
{
	CreateArrays();
}

void CubeMesh::CreateArrays()
{
	pVertexArray = (SimpleVertex*)vertexArray;
	pFaceIndexArray = (SimpleFace*)facesIndexArray;
}
