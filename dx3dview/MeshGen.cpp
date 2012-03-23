#include "meshGen.h"


/******************************************************************
*                                                                 *
*  Static Data                                                    *
*                                                                 *
******************************************************************/
const D3D10_INPUT_ELEMENT_DESC MeshGen::inputLayoutArray[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
	{ "NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
//	,{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0},
};


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

const SimpleVertex s_VertexArray[] =
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

const SHORT s_FacesIndexArray[] =
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


MeshGen::MeshGen(void)
{
	// Cube
	aCount = 2;
	bCount = 4;
	faceCount = aCount*bCount+aCount*bCount/2;

	// Sphere
	//aCount = 360;
	//bCount = 360;
	//faceCount = aCount*bCount*2;

	BuildMesh();
}


MeshGen::~MeshGen(void)
{
	DestroyArrays();
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
	//return FaceIndexArrayCount()*sizeof(SHORT);
	return FaceCount()*sizeof(SimpleFace);
	//return FaceIndexArrayCount()*3*sizeof(SHORT);
}

// Returns number of indexes in array
UINT MeshGen::FaceIndexArrayCount()
{
	return FaceCount() * 3; 
}

UINT MeshGen::FaceCount()
{
	// Cube
	//return aCount*bCount+aCount*bCount/2;

	// Sphere
	//return aCount*bCount*2; 
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

void MeshGen::BuildMesh()
{
	CreateArrays();
}

void MeshGen::CreateArrays()
{
	//pVertexArray = new SimpleVertex[aCount*bCount];
	//pFaceIndexArray = new SHORT[aCount*bCount*2];

	pVertexArray = (SimpleVertex*)s_VertexArray;
	pFaceIndexArray = (SimpleFace*)s_FacesIndexArray;
}

void MeshGen::DestroyArrays()
{
	//delete[] pFaceIndexArray;
	//delete[] pVertexArray;
}
