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
	SHORT GetVIndex(SHORT a, SHORT b);

private:
	SHORT divider;
	float r;
	float rr;
};

