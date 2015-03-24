#include "DirectxManager.h"
#include "ShaderManager.h"

DirectxManager::DirectxManager()
{
	device = 0;
	deviceContext = 0;
	swapChain = 0;
	renderTargetView = 0;
	depthStencilBuffer = 0;
	depthStencilState = 0;
	depthStencilView = 0;
}

bool DirectxManager::initialize(HWND window)
{
	HRESULT hr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

	//create swapChain desc
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

	//depth buffer desc
	ZeroMemory(&depthBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthBufferDesc.Width = DEFAULT_WINDOW_WIDTH;
	depthBufferDesc.Height = DEFAULT_WINDOW_HEIGHT;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0; 
	depthBufferDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&depthBufferDesc, NULL, &depthStencilBuffer);
	if (FAILED(hr))
		return false;

	//depth stencil desc
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true; 
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	//for front pixel
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//for back pixel
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//create the depth stencil state
	hr = device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);

	//initalize other 3D stuff


	deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	//create viewport for coordinates
	D3D11_VIEWPORT viewPort;
	ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;	
	viewPort.MaxDepth = 1.0f;
	viewPort.MinDepth = 0.0f;
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