#include "Object.h"

Object::Object() 
{
	vertexBuffer	= 0;
	indexBuffer		= 0;

	D3DXMatrixIdentity(&world);
}

void Object::initialize(ID3D11Device* device,ID3D11DeviceContext* deviceContext)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;

	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;

	//create vertices
	Vertex vertex[] =
	{
		{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.0f) },
		{ D3DXVECTOR3(-1.0f, +1.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ D3DXVECTOR3(+1.0f, +1.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.0f) },
		{ D3DXVECTOR3(+1.0f, -1.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ D3DXVECTOR3(-1.0f, -1.0f, +1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ D3DXVECTOR3(-1.0f, +1.0f, +1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ D3DXVECTOR3(+1.0f, +1.0f, +1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ D3DXVECTOR3(+1.0f, -1.0f, +1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) }
	};
	
	//create vertexbuffer desc	
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 8;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	ZeroMemory(&vertexData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexData.pSysMem = vertex;

	//create buffer
	device->CreateBuffer(&vertexBufferDesc, NULL, &vertexBuffer);

	//from directXTutorial : copy vertices into buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	deviceContext->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertex, sizeof(vertex));
	deviceContext->Unmap(vertexBuffer, NULL);	

	UINT indices[] = {
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	//create indexbuffer desc
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.ByteWidth = sizeof(UINT) * 36;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	
	ZeroMemory(&indexData, sizeof(D3D11_SUBRESOURCE_DATA));
	indexData.pSysMem = indices;

	//create buffer
	device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);	
}

void Object::render(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);		
}

D3DXMATRIX Object::getWorldMatrix()
{
	return world;
}