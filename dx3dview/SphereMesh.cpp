#include "SphereMesh.h"


SphereMesh::SphereMesh(void) : MeshGen()
{
	divider = 1;
	aCount = 360/divider;
	bCount = 181/divider; // Note there will be 360 duplicated vertices at both the 'top' and 'bottom' of the sphere

	faceCount = (VertexArrayCount() - aCount)*2; // The last ring of vertices will not have any outgoing faces

	r=2;

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

	for (UINT a = 0; a < aCount; a++)
	{
		for (UINT b = 0; b < bCount; b++) 
		{
			UINT vIndex = GetVIndex(a, b);

			float aRad = a*divider * (float)M_PI/180;
			float bRad = (b*divider+90) * (float)M_PI/180;

			// Set vertex position
			pVertexArray[vIndex].Pos.x = r * cos(bRad) * cos(aRad);
			pVertexArray[vIndex].Pos.y = r * cos(bRad) * sin(aRad);
			pVertexArray[vIndex].Pos.z = -r * sin(bRad);

			// Set Normal vector
			pVertexArray[vIndex].N.x = pVertexArray[vIndex].Pos.x;
			pVertexArray[vIndex].N.y = pVertexArray[vIndex].Pos.y;
			pVertexArray[vIndex].N.z = pVertexArray[vIndex].Pos.z;

			if (b < bCount-1) // The final vertex loop doesn't have linking faces
			{
				// Generate two faces for each new vertex
				pFaceIndexArray[faceIndex].v0 = GetVIndex(a, b);
				pFaceIndexArray[faceIndex].v1 = GetVIndex(a+1, b+1);
				pFaceIndexArray[faceIndex++].v2 = GetVIndex(a, b+1);

				pFaceIndexArray[faceIndex].v0 = GetVIndex(a, b);
				pFaceIndexArray[faceIndex].v1 = GetVIndex(a+1, b);
				pFaceIndexArray[faceIndex++].v2 = GetVIndex(a+1, b+1);
			}

		}
	}
}

UINT SphereMesh::GetVIndex(UINT a, UINT b)
{
	return (a%aCount * bCount + b);
}

void SphereMesh::CreateArrays()
{
	pVertexArray = new SimpleVertex[VertexArrayCount()];
	pFaceIndexArray = new SimpleFace[faceCount];
}

void SphereMesh::DestroyArrays()
{
	delete[] pFaceIndexArray;
	delete[] pVertexArray;
}