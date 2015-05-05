#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <d3d10_1.h>
#include <d3d10.h>
#include <D3DX10.h>
#include <D3D11.h>
#include <D3DX11.h>
#include <string>


class Renderable
{
private:
	
protected:
	ID3D11Device* m_Device;
	D3DXMATRIX m_WorldMatrix;
	std::wstring m_Name;

public:
	Renderable(ID3D11Device* device, const D3DXMATRIX* worldMatrix = NULL, const std::wstring name = L"Renderable");
	virtual void Create() = 0;
	virtual void Destroy() = 0;
	virtual void Render(ID3D11DeviceContext* diviceContext, UINT drawOrder, const D3DXMATRIX* viewMatrix, const D3DXMATRIX projMatrix) = 0;
	virtual void Update(double time, float elapsedTime){};
	std::wstring GetName(){ return m_Name; }
	std::wstring SetName(std::wstring name){ m_Name = name;}
	virtual void SetWorldMatrix(const D3DXMATRIX& value){ m_WorldMatrix = value; };
	virtual D3DXMATRIX* GetWorldMatrix(){ return &m_WorldMatrix; };
	virtual ~Renderable(){};


};
#endif