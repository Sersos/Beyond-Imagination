#include "Renderable.h"


Renderable::Renderable(ID3D11Device* device, const D3DXMATRIX* worldMatrix, const std::wstring name) : m_Name(name)
{
	m_Device = device;
	if (worldMatrix) m_WorldMatrix = *worldMatrix;
	else D3DXMatrixIdentity(&m_WorldMatrix);


}



