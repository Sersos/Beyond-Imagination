#ifndef OBJECT_H
#define OBJECT_H

#include "DirectxManager.h"

struct VertexPositionColor
{
	//D3DXVECTOR4 position;
	//D3DXVECTOR4 color;
};

struct VertexPositionNormal
{
	//D3DXVECTOR4 position;
	//D3DXVECTOR4 normal;
};

class Object
{
public:
	Object();

	virtual void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext) = 0;
	virtual void update(float delta) = 0;
	virtual void render(ID3D11DeviceContext* deviceContext) = 0;
	
private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;	
	ID3D11ShaderResourceView* texture;
};

#endif