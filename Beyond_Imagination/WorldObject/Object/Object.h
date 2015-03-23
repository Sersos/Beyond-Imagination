#ifndef OBJECT_H
#define OBJECT_H

#include "DirectxManager.h"

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR4 Color;	
};

class Object
{
public:
	Object();

	void initialize(ID3D11Device* device,ID3D11DeviceContext* deviceContext);	
	void render(ID3D11DeviceContext* deviceContext);
	

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;	

	ID3D11ShaderResourceView* texture;
};

#endif