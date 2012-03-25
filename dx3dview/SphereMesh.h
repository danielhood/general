#pragma once

#include <math.h>
#include "meshgen.h"

class SphereMesh :
	public MeshGen
{
public:
	SphereMesh(void);
	~SphereMesh(void);

protected:
	void BuildMesh();

private:
	void CreateArrays();
	void DestroyArrays();
	UINT GetVIndex(UINT a, UINT b);

private:
	float r;
	UINT divider;
};

