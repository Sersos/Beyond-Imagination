#include "Object.h"

Object::Object()
{

}


void Object::initialize(ID3D11Device* device,ID3D11DeviceContext* deviceContext)
{
	Vertex vertex[] =
	{
		{ D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ D3DXVECTOR3(0.5f, -0.5f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ D3DXVECTOR3(-0.5f, -0.5f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f) }
	};
	
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(Vertex)* 3;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexData.pSysMem = vertex;
	
	device->CreateBuffer(&bufferDesc,NULL,&vertexBuffer);

	//from directXTutorial : copy vertices into buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	deviceContext->Map(vertexBuffer,NULL, D3D11_MAP_WRITE_DISCARD,NULL,&ms);
	memcpy(ms.pData,vertex,sizeof(vertex));
	deviceContext->Unmap(vertexBuffer,NULL);
	
}

void Object::render(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->Draw(3, 0);

}