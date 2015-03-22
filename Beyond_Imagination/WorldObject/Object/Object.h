#ifndef OBJECT_H
#define OBJECT_H

#include "DirectxManager.h"

struct Vertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;	
};

class Object
{
public:
	Object();

	void initialize(ID3D11Device* device, Vertex vertex[]);	
	void render(ID3D11DeviceContext* deviceContext);
	
private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;	
	ID3D11ShaderResourceView* texture;
};

#endif