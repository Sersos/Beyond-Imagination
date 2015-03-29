#include "Object.h"
#include "ShaderManager.h"

Object::Object() 
{
	vertexBuffer	= 0;
	indexBuffer		= 0;
	scale = 0;
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
		D3DXVECTOR3(-0.5f, -1.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f),
		D3DXVECTOR3(-1.0f, +1.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f),
		D3DXVECTOR3(+1.0f, +1.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f),
		D3DXVECTOR3(+1.0f, -1.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f),
		D3DXVECTOR3(-1.0f, -1.0f, +1.0f), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f),
		D3DXVECTOR3(-1.0f, +1.0f, +1.0f), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f),
		D3DXVECTOR3(+1.0f, +1.0f, +1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR3(+1.0f, -1.0f, +1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) 
	};
	
	//create vertexbuffer desc	
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 8;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	
	
	vertexData.pSysMem = vertex;

	//create buffer
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

	////from directXTutorial : copy vertices into buffer
	//D3D11_MAPPED_SUBRESOURCE ms;
	//deviceContext->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	//memcpy(ms.pData, vertex, sizeof(vertex));
	//deviceContext->Unmap(vertexBuffer, NULL);	

	DWORD indices[] = {
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
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * 36;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;		
	indexData.pSysMem = indices;

	//create buffer
	device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);	

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
}

void Object::update()
{
	scale += 0.0005f;
	D3DXMatrixRotationZ(&world, scale);
}

void Object::render(ID3D11DeviceContext* deviceContext, ShaderManager* shaderManager, D3DXMATRIX view, D3DXMATRIX projection)
{
	D3DXMATRIX worldViewProjection = world * view * projection;
	
	D3DX11_TECHNIQUE_DESC techniqueDesc;
	shaderManager->effectTechnique->GetDesc(&techniqueDesc);
	shaderManager->effectWorldViewProjection->SetMatrix((float*)worldViewProjection);

	for (UINT p = 0; p < techniqueDesc.Passes; ++p)
	{
		shaderManager->effectTechnique->GetPassByIndex(p)->Apply(0, deviceContext);
		deviceContext->DrawIndexed(36, 0, 0);
	}
}

D3DXMATRIX Object::getWorldMatrix()
{
	return world;
}