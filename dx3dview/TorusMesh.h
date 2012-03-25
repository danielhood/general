#pragma once

#include <math.h>
#include "meshgen.h"

class TorusMesh :
	public MeshGen
{
public:
	TorusMesh(void);
	~TorusMesh(void);

protected:
	void BuildMesh();

private:
	void CreateArrays();
	void DestroyArrays();
	UINT GetVIndex(UINT a, UINT b);

private:
	UINT divider;
	float r;
	float rr;
};

