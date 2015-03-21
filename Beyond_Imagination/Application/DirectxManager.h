#ifndef DIRECTXMANAGER_H
#define DIRECTXMANAGER_H

#include <D3D10_1.h>
#include <D3D10.h>
#include <D3DX10.h>
#include <D3D11.h>
#include <D3DX11.h>
#include <Windows.h>
#include <WindowsX.h>

class ShaderManager;

class DirectxManager
{
public:
	DirectxManager();

	bool initialize(HWND window);
	void beginScene();
	void presentScene();
	void close();

	void switchToFullScreen();
	void enableSamplerState(){ }; //if shader with texture is used
	void enableStencilBuffer() { };
	void enableRasterizerState() { };

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ShaderManager* shaderManager;

};

#endif