#ifndef DIRECTXMANAGER_H
#define DIRECTXMANAGER_H

#include <d3d10_1.h>
#include <d3d10.h>
#include <d3d11.h>
#include <Windows.h>
#include <WindowsX.h>

class DirectxManager
{
public:
	DirectxManager();

	void initialize(HWND window);

	void beginScene();
	void presentScene();
	void close();

	void switchToFullScreen();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;

};

#endif