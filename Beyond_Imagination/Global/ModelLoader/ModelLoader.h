#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "DirectxManager.h"
#include "Global.h"
#include <string>
#include <vector>

struct ModelData
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
};

struct Face
{
	int a, b, c;
};

class ModelLoader
{
public:
	ModelLoader(); 

	void loadObject(const char* filename);	

	std::vector <ModelData> m_vertices;
	std::vector <Face> m_indices;

	long m_indexCount;
	long m_vertexCount;	
};

#endif