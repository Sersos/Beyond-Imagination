#ifndef OBJECT_H
#define OBJECT_H

#include "DirectxManager.h"

struct Vertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
	D3DXVECTOR3 normal;
};

class Object
{
public:
	Object(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	virtual void initialize(Vertex* vertex) = 0;
	void update(float delta);
	virtual void render(ID3D11DeviceContext* deviceContext) = 0;
	
private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;	
	ID3D11ShaderResourceView* texture;
};

#endif