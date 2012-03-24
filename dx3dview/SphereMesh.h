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
	SHORT GetVIndex(SHORT a, SHORT b);

private:
	float r;
	UINT divider;
};

