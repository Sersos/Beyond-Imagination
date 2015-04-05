#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem()
{
	m_vertexBuffer = NULL;
	m_inputLayout = NULL;
}

void CoordinateSystem::initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	HRESULT result;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	ID3D10Blob* compiledShader;

	Axis axis[SIZE * 6 * 2];
	int i = 0;

	//Y
	for (int x = -SIZE / 2; x < SIZE / 2; x++)
	{
		axis[i].Position = D3DXVECTOR3(x * SPACING, -SIZE, 0.0f);
		axis[i].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.5f);
		i++;
		axis[i].Position = D3DXVECTOR3(x * SPACING, SIZE, 0.0f);
		axis[i].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.5f);
		i++;

		axis[i].Position = D3DXVECTOR3(-SIZE, x * SPACING, 0.0f);
		axis[i].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.5f);
		i++;
		axis[i].Position = D3DXVECTOR3(SIZE, x * SPACING, 0.0f);
		axis[i].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.5f);
		i++;
	}

	//Z
	for (int y = -SIZE / 2; y < SIZE / 2; y++)
	{
		axis[i].Position = D3DXVECTOR3(0.0f, y * SPACING, -SIZE);
		axis[i].Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.5f);
		i++;
		axis[i].Position = D3DXVECTOR3(0.0f, y * SPACING, SIZE);
		axis[i].Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.5f);
		i++;

		axis[i].Position = D3DXVECTOR3(0.0f, -SIZE, y * SPACING);
		axis[i].Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.5f);
		i++;
		axis[i].Position = D3DXVECTOR3(0.0f, SIZE, y * SPACING);
		axis[i].Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.5f);
		i++;
	}

	//X
	for (int z = -SIZE / 2; z < SIZE / 2; z++)
	{
		axis[i].Position = D3DXVECTOR3(-SIZE, 0.0f, z * SPACING);
		axis[i].Color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		i++;
		axis[i].Position = D3DXVECTOR3(SIZE, 0.0f, z * SPACING);
		axis[i].Color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		i++;

		axis[i].Position = D3DXVECTOR3(z * SPACING, 0.0f, -SIZE);
		axis[i].Color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		i++;
		axis[i].Position = D3DXVECTOR3(z * SPACING, 0.0f, SIZE);
		axis[i].Color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		i++;
	}

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Axis) * SIZE * 6 * 2;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	vertexData.pSysMem = axis;

	//create buffer
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	D3DXMatrixIdentity(&m_world);

	result = D3DX11CompileFromFile(L"Global/Shader/CoordinateSystem.fx", 0, 0, 0, "fx_5_0", 0, 0, 0, &compiledShader, NULL, 0);
	if (FAILED(result))
		MessageBox(0, L"Cant load CoordinateSystem.fx", 0, MB_OK);

	result = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, device, &m_effect);
	if (FAILED(result))
		MessageBox(0, L"Cant create effect", 0, MB_OK);

	m_effectTechnique = m_effect->GetTechniqueByName("CoordinateSystem");
	m_effectWorldViewProjection = m_effect->GetVariableByName("gWorldViewProjection")->AsMatrix();

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	D3DX11_PASS_DESC passDesc;
	m_effectTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
	device->CreateInputLayout(layout, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_inputLayout);

	deviceContext->IASetInputLayout(m_inputLayout);
}

void CoordinateSystem::update()
{

}

void CoordinateSystem::render(ID3D11DeviceContext* deviceContext, D3DXMATRIX view, D3DXMATRIX projection)
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	
	D3DXMATRIX worldViewProjection = m_world * view * projection;
	m_effectWorldViewProjection->SetMatrix((float*)worldViewProjection);

	UINT stride = sizeof(Axis);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	D3DX11_TECHNIQUE_DESC techniqueDesc;
	m_effectTechnique->GetDesc(&techniqueDesc);

	for (UINT p = 0; p < techniqueDesc.Passes; ++p)
	{
		m_effectTechnique->GetPassByIndex(p)->Apply(0, deviceContext);
		deviceContext->Draw(SIZE * 6 * 2, 0);
	}
}

void CoordinateSystem::close()
{
	ReleaseCOM(m_vertexBuffer);
	ReleaseCOM(m_inputLayout);
	ReleaseCOM(m_effect);
}

