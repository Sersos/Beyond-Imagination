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

class ModelLoader
{
public:
	ModelLoader(); 

	void loadObject(const char* filename);	

	std::vector <ModelData> m_vertices;
	std::vector <int> m_indices;

	int m_indexCount;
	int m_vertexCount;	
};

#endif