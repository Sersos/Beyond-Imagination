#include "DirectxManager.h"
#include "ShaderManager.h"


DirectxManager::DirectxManager()
{
	m_device = 0;
	m_deviceContext = 0;
	m_swapChain = 0;
	m_renderTargetView = 0;
	m_depthStencilBuffer = 0;
	m_depthStencilState = 0;
	m_depthStencilView = 0;
	m_rasterizerState = 0;
	m_blendState = 0;
}

bool DirectxManager::initialize(HWND window, bool wireFrame)
{
	HRESULT hr;	

	//create swapChain desc
	ZeroMemory(&m_swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	m_swapChainDesc.BufferCount = 1;
	m_swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_swapChainDesc.BufferDesc.Width = 1280; //window width
	m_swapChainDesc.BufferDesc.Height = 720; // window height
	m_swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_swapChainDesc.OutputWindow = window;
	m_swapChainDesc.SampleDesc.Count = 1;
	m_swapChainDesc.SampleDesc.Quality = 0;
	m_swapChainDesc.Windowed = true;
	m_swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//not completed	
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&m_swapChainDesc,
		&m_swapChain,
		&m_device,
		NULL,
		&m_deviceContext);

	if (FAILED(hr))
		return false;	

	ID3D11Texture2D* pointerBackBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pointerBackBuffer);

	m_device->CreateRenderTargetView(pointerBackBuffer, NULL, &m_renderTargetView);

	pointerBackBuffer->Release();
	pointerBackBuffer = 0;

	//depth buffer desc
	ZeroMemory(&m_depthBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
	m_depthBufferDesc.Width = DEFAULT_WINDOW_WIDTH;
	m_depthBufferDesc.Height = DEFAULT_WINDOW_HEIGHT;
	m_depthBufferDesc.MipLevels = 1;
	m_depthBufferDesc.ArraySize = 1;
	m_depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	m_depthBufferDesc.SampleDesc.Count = 1;
	m_depthBufferDesc.SampleDesc.Quality = 0;
	m_depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	m_depthBufferDesc.CPUAccessFlags = 0;
	m_depthBufferDesc.MiscFlags = 0;

	hr = m_device->CreateTexture2D(&m_depthBufferDesc, NULL, &m_depthStencilBuffer);
	if (FAILED(hr))
		return false;

	//depth stencil desc
	ZeroMemory(&m_depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	m_depthStencilDesc.DepthEnable = true;
	m_depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	m_depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	m_depthStencilDesc.StencilEnable = true;
	m_depthStencilDesc.StencilReadMask = 0xFF;
	m_depthStencilDesc.StencilWriteMask = 0xFF;

	//for front pixel
	m_depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	m_depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	m_depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	m_depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//for back pixel
	m_depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	m_depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	m_depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	m_depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//create the depth stencil state
	hr = m_device->CreateDepthStencilState(&m_depthStencilDesc, &m_depthStencilState);

	//finally set depth stencil state
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	//fill depthstencilviewdesc with data
	ZeroMemory(&m_depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	m_depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	m_depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	m_depthStencilViewDesc.Texture2D.MipSlice = 0;

	//create depthstencilview
	hr = m_device->CreateDepthStencilView(m_depthStencilBuffer, &m_depthStencilViewDesc, &m_depthStencilView);
	if (FAILED(hr))
		return false;

	enableBlend(true);

	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	//setup rasterizerdesc
	ZeroMemory(&m_rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	m_rasterizerDesc.AntialiasedLineEnable = false;
	m_rasterizerDesc.CullMode = D3D11_CULL_NONE;
	m_rasterizerDesc.DepthBias = 0;
	m_rasterizerDesc.DepthBiasClamp = 0.0f;
	m_rasterizerDesc.DepthClipEnable = true;
	if (wireFrame)
	{
		//enable wireframe mode, only lines will be drawn
		enableWireFrame();
	}		
	else
	{
		m_rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	}	

	m_rasterizerDesc.FrontCounterClockwise = false;
	m_rasterizerDesc.MultisampleEnable = false;
	m_rasterizerDesc.ScissorEnable = false;
	m_rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	//create rasterizerstate
	hr = m_device->CreateRasterizerState(&m_rasterizerDesc, &m_rasterizerState);

	//set rasterizerstate
	m_deviceContext->RSSetState(m_rasterizerState);

	//create viewport for coordinates
	D3D11_VIEWPORT viewPort;
	ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;	
	viewPort.MaxDepth = 1.0f;
	viewPort.MinDepth = 0.0f;
	viewPort.Width = DEFAULT_WINDOW_WIDTH;
	viewPort.Height = DEFAULT_WINDOW_HEIGHT;

	m_deviceContext->RSSetViewports(1, &viewPort);
	return true;
}

void DirectxManager::beginScene()
{
	float backgroundColor[4] = { 0.7f, 0.2f, 0.2f, 0.5f };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, backgroundColor);	
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

ID3D11Device* DirectxManager::getDevice()
{
	return m_device;
}

ID3D11DeviceContext* DirectxManager::getDeviceContext()
{
	return m_deviceContext;
}

void DirectxManager::presentScene()
{
	//show content of swapChain
	m_swapChain->Present(0, 0);
}

void DirectxManager::enableWireFrame()
{
	m_rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
}

void DirectxManager::enableBlend(bool blend)
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc,	sizeof(D3D11_BLEND_DESC));
	blendDesc.RenderTarget[0].BlendEnable = blend;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.75, 0.75, 0.75, 1.0f };

	m_device->CreateBlendState(&blendDesc, &m_blendState);	
	m_deviceContext->OMSetBlendState(m_blendState, blendFactor, 0xffffffff);
}

void DirectxManager::switchToFullScreen()
{
	m_swapChainDesc.Windowed = false;
}

void DirectxManager::close()
{
	ReleaseCOM(m_device);
	ReleaseCOM(m_deviceContext);
	ReleaseCOM(m_swapChain);
	ReleaseCOM(m_renderTargetView);
	ReleaseCOM(m_depthStencilBuffer);
	ReleaseCOM(m_depthStencilState);
	ReleaseCOM(m_depthStencilView);
	ReleaseCOM(m_rasterizerState);
	ReleaseCOM(m_blendState);
	
}