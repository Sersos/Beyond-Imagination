#ifndef OBJECT_H
#define OBJECT_H

#include "DirectxManager.h"
#include "ShaderManager.h"
#include "Transform.h"

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;	
};

class Object
{
public:
	Object();

	void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, D3DXVECTOR3 origin);
	void update();
	void render(ID3D11DeviceContext* deviceContext, ShaderManager* shaderManager, D3DXMATRIX view, D3DXMATRIX projection);	

private:
	//buffers for vertices and indices
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;		

	D3DXMATRIX m_positionMatrix;
	D3DXMATRIX m_rotationMatrix;
	D3DXMATRIX m_scaleMatrix;

	//world matrix, manipulate in "update-funtion"
	D3DXMATRIX m_world;	
	
};

#endif