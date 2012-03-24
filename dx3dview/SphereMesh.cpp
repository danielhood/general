#include "SphereMesh.h"


SphereMesh::SphereMesh(void) : MeshGen()
{
	divider = 8;
	aCount = 360/(SHORT)divider;
	bCount = 360/(SHORT)divider;
	faceCount = aCount*bCount*2;

	r=1.5;

	fillMode = D3D10_FILL_WIREFRAME;
}


SphereMesh::~SphereMesh(void)
{
	DestroyArrays();
}

void SphereMesh::BuildMesh()
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
			//pVertexArray[vIndex].Pos.x = r * sin(aRad) * sin(bRad); // Pillow!
			//pVertexArray[vIndex].Pos.x = r * sin(aRad) + sin(bRad); // Wrong, but really neat!

			pVertexArray[vIndex].Pos.x = r * (sin(aRad) + sin(bRad));

			pVertexArray[vIndex].Pos.y = r * cos(aRad);
			pVertexArray[vIndex].Pos.z = r * cos(bRad);

			// Set Normal vector
			pVertexArray[vIndex].N.x = pVertexArray[vIndex].Pos.x;
			pVertexArray[vIndex].N.y = pVertexArray[vIndex].Pos.y;
			pVertexArray[vIndex].N.z = pVertexArray[vIndex].Pos.z;

			// Generate two faces for each new vertex
			pFaceIndexArray[faceIndex].v0 = GetVIndex(a, b);
			pFaceIndexArray[faceIndex].v1 = GetVIndex(a+1, b);
			pFaceIndexArray[faceIndex++].v2 = GetVIndex(a, b+1);

			pFaceIndexArray[faceIndex].v0 = GetVIndex(a+1, b);
			pFaceIndexArray[faceIndex].v1 = GetVIndex(a+1, b+1);
			pFaceIndexArray[faceIndex++].v2 = GetVIndex(a, b+1);
		}
	}
}

SHORT SphereMesh::GetVIndex(SHORT a, SHORT b)
{
	return (a * bCount + b)%VertexArrayCount();
}

void SphereMesh::CreateArrays()
{
	pVertexArray = new SimpleVertex[aCount*bCount];
	pFaceIndexArray = new SimpleFace[aCount*bCount*2];
}

void SphereMesh::DestroyArrays()
{
	delete[] pFaceIndexArray;
	delete[] pVertexArray;
}