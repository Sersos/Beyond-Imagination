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

	void loadObject(const char* filename, bool texture);

	int getIndexCount();
	int getVertexCount();
	int getFaceCount();	

	std::vector<ModelData> m_vertices;
	std::vector<Face> m_indices;

private:
	int m_indexCount;
	int m_vertexCount;
	int m_faceCount;
};

#endif