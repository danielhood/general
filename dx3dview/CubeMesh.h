#pragma once
#include "meshgen.h"
class CubeMesh :
	public MeshGen
{
public:
	CubeMesh(void);
	~CubeMesh(void);

protected:
	static const SimpleVertex vertexArray[];
	static const SHORT facesIndexArray[];

protected:
	void BuildMesh();

private:
	void CreateArrays();
};

