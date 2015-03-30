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
	rasterizerState = 0;
}

bool DirectxManager::initialize(HWND window, bool wireFrame)
{
	HRESULT hr;	

	//create swapChain desc
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = 1280; //window width
	swapChainDesc.BufferDesc.Height = 720; // window height
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window;
	swapChainDesc.SampleDesc.Count = 1;
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

	//finally set depth stencil state
	deviceContext->OMSetDepthStencilState(depthStencilState, 1);

	//fill depthstencilviewdesc with data
	ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	//create depthstencilview
	hr = device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &depthStencilView);
	if (FAILED(hr))
		return false;

	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	//setup rasterizerdesc
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.AntialiasedLineEnable = false;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = true;
	if (wireFrame)
	{
		//enable wireframe mode, only lines will be drawn
		enableWireFrame();
	}		
	else
	{
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	}	

	rasterizerDesc.FrontCounterClockwise = false; 
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.ScissorEnable = false; 
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	//create rasterizerstate
	hr = device->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

	//set rasterizerstate
	deviceContext->RSSetState(rasterizerState);

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
	float backgroundColor[4] = { 0.35, 0.7f, 0.7f, 0.5f };
	deviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);	
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
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

void DirectxManager::enableWireFrame()
{
	rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
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