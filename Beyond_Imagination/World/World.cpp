#include "World.h"

World::World::World()
{
	//initialize directx objects
	m_vertexBuffer = 0;
	m_indexBuffer  = 0;
}

void World::World::initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, uint8 width, uint8 depth)
{
	//vertex & index descs
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;


}