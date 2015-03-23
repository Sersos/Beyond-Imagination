#include "DirectxManager.h"
#include "ShaderManager.h"

DirectxManager::DirectxManager()
{
	device = 0;
	deviceContext = 0;
	swapChain = 0;
	renderTargetView = 0;
}

bool DirectxManager::initialize(HWND window)
{
	HRESULT hr;
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
	hr = D3D11CreateDeviceAndSwapChain(
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

	if (FAILED(hr))
		return false;	

	ID3D11Texture2D* pointerBackBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pointerBackBuffer);

	device->CreateRenderTargetView(pointerBackBuffer, NULL, &renderTargetView);

	pointerBackBuffer->Release();
	pointerBackBuffer = 0;

	deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	D3D11_VIEWPORT viewPort;
	ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = DEFAULT_WINDOW_WIDTH;
	viewPort.Height = DEFAULT_WINDOW_HEIGHT;

	deviceContext->RSSetViewports(1, &viewPort);



	return true;
}

void DirectxManager::beginScene()
{
	float backgroundColor[4] = { 0.5f, 0.5f, 0, 0.5f };
	deviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);		
}

ID3D11Device* DirectxManager::getDevice()
{
	return device;
}

ID3D11DeviceContext* DirectxManager::getDeviceContext()
{
	return deviceContext;
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