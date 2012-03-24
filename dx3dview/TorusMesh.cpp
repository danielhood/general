#include "TorusMesh.h"


TorusMesh::TorusMesh(void)
{
	divider = 8;
	aCount = 360/divider;
	bCount = 360/divider;

	faceCount = aCount*bCount*2;

	r=1.5;
	rr=0.5;

	fillMode = D3D10_FILL_WIREFRAME;
	//fillMode = D3D10_FILL_SOLID;
}


TorusMesh::~TorusMesh(void)
{
	DestroyArrays();
}

void TorusMesh::BuildMesh()
{
	CreateArrays();

	UINT faceIndex = 0;

	for (SHORT a = 0; a < aCount; a++)
	{
		for (SHORT b = 0; b < bCount; b++)
		{
			SHORT vIndex = GetVIndex(a, b);

			float aRad = a*divider * (float)M_PI / 180;
			float bRad = b*divider * (float)M_PI / 180;

			// Set vertex position
			pVertexArray[vIndex].Pos.x = (rr + r * sin(aRad)) * sin(bRad);
			pVertexArray[vIndex].Pos.z = r * cos(aRad);
			pVertexArray[vIndex].Pos.y = -(rr + r * sin(aRad)) * cos(bRad);;

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

SHORT TorusMesh::GetVIndex(SHORT a, SHORT b)
{
	return (a * bCount + b)%VertexArrayCount();
}

void TorusMesh::CreateArrays()
{
	pVertexArray = new SimpleVertex[aCount*bCount];
	pFaceIndexArray = new SimpleFace[aCount*bCount*2];
}

void TorusMesh::DestroyArrays()
{
	delete[] pFaceIndexArray;
	delete[] pVertexArray;
}
