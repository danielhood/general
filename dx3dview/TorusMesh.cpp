#include "TorusMesh.h"


TorusMesh::TorusMesh(void)
{
	divider = 1;
	aCount = 360/divider;
	bCount = 360/divider;

	faceCount = VertexArrayCount()*2;

	r=0.25;
	rr=3;

	//fillMode = D3D10_FILL_WIREFRAME;
}


TorusMesh::~TorusMesh(void)
{
	DestroyArrays();
}

void TorusMesh::BuildMesh()
{
	CreateArrays();

	UINT faceIndex = 0;

	for (UINT a = 0; a < aCount; a++)
	{
		for (UINT b = 0; b < bCount; b++)
		{
			UINT vIndex = GetVIndex(a, b);

			float aRad = a*divider * (float)M_PI / 180;
			float bRad = b*divider * (float)M_PI / 180;

			// Set vertex position
			pVertexArray[vIndex].Pos.x = (rr + r * cos(aRad)) * sin(bRad);
			pVertexArray[vIndex].Pos.y = r * sin(aRad);
			pVertexArray[vIndex].Pos.z = (rr + r * cos(aRad)) * cos(bRad);;

			// Set Normal vector
			pVertexArray[vIndex].N.x = pVertexArray[vIndex].Pos.x;
			pVertexArray[vIndex].N.y = pVertexArray[vIndex].Pos.y;
			pVertexArray[vIndex].N.z = pVertexArray[vIndex].Pos.z;

			// Generate two faces for each new vertex
			pFaceIndexArray[faceIndex].v0 = GetVIndex(a, b);
			pFaceIndexArray[faceIndex].v1 = GetVIndex(a, b+1);
			pFaceIndexArray[faceIndex++].v2 = GetVIndex(a+1, b);

			pFaceIndexArray[faceIndex].v0 = GetVIndex(a, b+1);
			pFaceIndexArray[faceIndex].v1 = GetVIndex(a+1, b+1);
			pFaceIndexArray[faceIndex++].v2 = GetVIndex(a+1, b);
		}
	}
}

UINT TorusMesh::GetVIndex(UINT a, UINT b)
{
	return (a%aCount * bCount + b%bCount);
}

void TorusMesh::CreateArrays()
{
	pVertexArray = new SimpleVertex[VertexArrayCount()];
	pFaceIndexArray = new SimpleFace[faceCount];
}

void TorusMesh::DestroyArrays()
{
	delete[] pFaceIndexArray;
	delete[] pVertexArray;
}
