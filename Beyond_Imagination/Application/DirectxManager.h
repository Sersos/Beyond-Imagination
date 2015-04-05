#ifndef DIRECTXMANAGER_H
#define DIRECTXMANAGER_H

#include <d3d10_1.h>
#include <d3d10.h>
#include <D3DX10.h>
#include <D3D11.h>
#include <D3DX11.h>
#include <d3dx11effect.h>
#include <Windows.h>
#include <WindowsX.h>

class DirectxManager
{
public:
	DirectxManager();

	bool initialize(HWND window, bool wireFrame);
	void beginScene();
	void presentScene();
	void close();

	void switchToFullScreen();
	void enableBlend(bool blend);
	void enableWireFrame();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

private:
	//important structs d3d11
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterizerState;
	ID3D11BlendState* m_blendState;

	//important descs for different functions
	DXGI_SWAP_CHAIN_DESC m_swapChainDesc;
	D3D11_TEXTURE2D_DESC m_depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC m_depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC m_depthStencilViewDesc;
	D3D11_RASTERIZER_DESC m_rasterizerDesc;

};

#endif