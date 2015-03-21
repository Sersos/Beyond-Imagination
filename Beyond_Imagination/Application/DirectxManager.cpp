#include "DirectxManager.h"

DirectxManager::DirectxManager()
{
	device = 0;
	deviceContext = 0;
	swapChain = 0;
	renderTargetView = 0;
}

void DirectxManager::initialize(HWND window)
{
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = 1280; //window width
	swapChainDesc.BufferDesc.Height = 720; // window height
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window;
	swapChainDesc.SampleDesc.Count = 4;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//not completed
	
	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device,
		NULL,
		&deviceContext);

}

void DirectxManager::presentScene()
{
	//show content of swapChain
	swapChain->Present(0, 0);
}

void DirectxManager::switchToFullScreen()
{
	swapChainDesc.Windowed = false;
}

void DirectxManager::close()
{
	if (device)
		device->Release();

	if (deviceContext)
		deviceContext->Release();

	if (swapChain)
		swapChain->Release();

	if (renderTargetView)
		renderTargetView->Release();
}