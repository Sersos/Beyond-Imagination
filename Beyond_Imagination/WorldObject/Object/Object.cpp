#include "Object.h"
#include "ShaderManager.h"

Object::Object() 
{
	vertexBuffer	= 0;
	indexBuffer		= 0;
	m_model = new ModelLoader();
}

void Object::initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;

	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;
	
	m_model->loadObject("spaceShipModel.obj");

	D3DXVECTOR3 normal;
	/*
	//create vertices
	Vertex vertex[] =
	{
		
		D3DXVECTOR3(-1.0f, -1.0f, -1.0f), *D3DXVec3Normalize(&normal ,&D3DXVECTOR3(-1.0f, -1.0f, -1.0f)),
		D3DXVECTOR3(-1.0f, +1.0f, -1.0f), *D3DXVec3Normalize(&normal, &D3DXVECTOR3(-1.0f, +1.0f, -1.0f)),
		D3DXVECTOR3(+1.0f, +1.0f, -1.0f), *D3DXVec3Normalize(&normal, &D3DXVECTOR3(+1.0f, +1.0f, -1.0f)),
		D3DXVECTOR3(+1.0f, -1.0f, -1.0f), *D3DXVec3Normalize(&normal, &D3DXVECTOR3(+1.0f, -1.0f, -1.0f)),
		D3DXVECTOR3(-1.0f, -1.0f, +1.0f), *D3DXVec3Normalize(&normal, &D3DXVECTOR3(-1.0f, -1.0f, +1.0f)),
		D3DXVECTOR3(-1.0f, +1.0f, +1.0f), *D3DXVec3Normalize(&normal, &D3DXVECTOR3(-1.0f, +1.0f, +1.0f)),
		D3DXVECTOR3(+1.0f, +1.0f, +1.0f), *D3DXVec3Normalize(&normal, &D3DXVECTOR3(+1.0f, +1.0f, +1.0f)),
		D3DXVECTOR3(+1.0f, -1.0f, +1.0f), *D3DXVec3Normalize(&normal, &D3DXVECTOR3(+1.0f, -1.0f, +1.0f))

		/*D3DXVECTOR3(origin.x + 0.5f, origin.y + 0.5f, origin.z + 0.5f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f),
		D3DXVECTOR3(origin.x + 0.5f, origin.y - 0.5f, origin.z + 0.5f), D3DXVECTOR4(0.5f, 0.0f, 1.0f, 1.0f),
		D3DXVECTOR3(origin.x - 0.5, origin.y - 0.5, origin.z + 0.5), D3DXVECTOR4(0.5f, 1.0f, 0.0f, 1.0f),
		D3DXVECTOR3(origin.x - 0.5, origin.y + 0.5, origin.z + 0.5), D3DXVECTOR4(0.5f, 1.0f, 0.0f, 1.0f),
		D3DXVECTOR3(origin.x + 0.5f, origin.y + 0.5f, origin.z - 0.5f), D3DXVECTOR4(0.5f, 0.0f, 1.0f, 1.0f),
		D3DXVECTOR3(origin.x + 0.5f, origin.y - 0.5f, origin.z - 0.5f), D3DXVECTOR4(0.5f, 0.0f, 1.0f, 1.0f),
		D3DXVECTOR3(origin.x - 0.5, origin.y - 0.5, origin.z - 0.5), D3DXVECTOR4(0.5f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR3(origin.x - 0.5, origin.y + 0.5, origin.z - 0.5), D3DXVECTOR4(0.5f, 0.0f, 0.0f, 1.0f)
	};
	*/
	
	
	//create vertexbuffer desc	
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(ModelData) * m_model->m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	
	
	vertexData.pSysMem = &m_model->m_vertices[0];

	//create buffer
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	/*
	DWORD indices[] = {
		// front face
		4, 5, 7,
		5, 6, 7,

		// back face
		0, 1, 3,
		1, 2, 3,

		// left face
		2, 3, 7,
		2, 6, 7,

		// right face
		0, 1, 4,
		1, 4, 5,

		// top face
		0, 3, 4,
		3, 4, 7,

		// bottom face
		1, 2, 5,
		2, 5, 6
	};
	*/	

	//create indexbuffer desc
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(uint8) * m_model->m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;		
	indexData.pSysMem = &m_model->m_indices[0];

	//create buffer
	device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);	
	
	D3DXMatrixIdentity(&m_world);
	Transform::rotate(&m_rotationMatrix, D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	Transform::scale(&m_scaleMatrix, D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	Transform::translate(&m_positionMatrix, D3DXVECTOR3(0, 0, 1));
	//Transform::translate(&m_positionMatrix, D3DXVECTOR3(5.0f, 5.0f, 5.0f));
}

void Object::update()
{
	
}

void Object::render(ID3D11DeviceContext* deviceContext, ShaderManager* shaderManager, D3DXMATRIX view, D3DXMATRIX projection)
{
	UINT stride = sizeof(ModelData);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	m_world = m_rotationMatrix * m_scaleMatrix  * m_positionMatrix;
	D3DXMATRIX worldViewProjection = m_world * view * projection;
	D3DXMATRIX worldInvTranspose = LightHelper::inverseTranspose(&m_world);
	
	shaderManager->m_effectWorldViewProjection->SetMatrix((float*)worldViewProjection);
	shaderManager->m_effectWorld->SetMatrix((float*)m_world);
	shaderManager->m_effectWorldInvTranspose->SetMatrix((float*)worldInvTranspose);
	
	D3DX11_TECHNIQUE_DESC techniqueDesc;
	shaderManager->m_effectTechnique->GetDesc(&techniqueDesc);

	for (UINT p = 0; p < techniqueDesc.Passes; ++p)
	{
		shaderManager->m_effectTechnique->GetPassByIndex(p)->Apply(0, deviceContext);
		deviceContext->DrawIndexed(m_model->m_indexCount, 0, 0);
	}
}

