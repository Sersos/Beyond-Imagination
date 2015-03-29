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

class ShaderManager;

class DirectxManager
{
public:
	DirectxManager();

	bool initialize(HWND window, bool wireFrame);
	void beginScene();
	void presentScene();
	void close();

	void switchToFullScreen();
	void enableSamplerState(){ }; //if shader with texture is used
	void enableStencilBuffer() { };
	void enableWireFrame();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

private:
	//important structs d3d11
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11RasterizerState* rasterizerState;

	//important descs for different functions
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterizerDesc;

};

#endif