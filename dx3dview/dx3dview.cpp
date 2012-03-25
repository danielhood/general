// Simple implementation of DirectX 10 for viewing a hard coded set of 
// triangles defined by constant arrays.

#include "dx3dview.h"

using namespace std;

#pragma region WinMain

/******************************************************************
*                                                                 *
*  WinMain                                                        *
*                                                                 *
*  Application entrypoint                                         *
*                                                                 *
******************************************************************/

int WINAPI WinMain(
	HINSTANCE /*hInstance*/,
	HINSTANCE /*hPrevInstance*/,
	LPSTR /*lpCmdLine*/,
	int /*nCmdShow*/
	)
{
	// Ignore the return value because we want to continue running even in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			DemoApp app;

			if (SUCCEEDED(app.Initialize()))
			{
				app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}

#pragma endregion

#pragma region DemoApp

#pragma region Constructor and Initialization
/******************************************************************
*                                                                 *
*  DemoApp::DemoApp constructor                                   *
*                                                                 *
*  Initialize member data                                         *
*                                                                 *
******************************************************************/

DemoApp::DemoApp() :
	m_hwnd(NULL),
		m_pDevice(NULL),
		m_pSwapChain(NULL),
		m_pState(NULL),
		m_pRenderTargetView(NULL),
		m_pDepthStencil(NULL),
		m_pDepthStencilView(NULL),
		m_pShader(NULL),
		m_pVertexBuffer(NULL),
		m_pVertexLayout(NULL),
		m_pFacesIndexBuffer(NULL),
		m_pTechniqueNoRef(NULL),
		m_pWorldVariableNoRef(NULL),
		m_pViewVariableNoRef(NULL),
		m_pProjectionVariableNoRef(NULL)
	{
		m_appState.dx = 0;
		m_appState.dy = 0;
		m_appState.running = false;

		//pMeshGen = new CubeMesh;
		//pMeshGen = new SphereMesh;
		pMeshGen = new TorusMesh;
		pMeshGen->Init();
	}

	/******************************************************************
	*                                                                 *
	*  DemoApp::~DemoApp destructor                                   *
	*                                                                 *
	*  Tear down resources                                            *
	*                                                                 *
	******************************************************************/

	DemoApp::~DemoApp()
	{
		SafeRelease(&m_pDevice);
		SafeRelease(&m_pSwapChain);
		SafeRelease(&m_pState);
		SafeRelease(&m_pRenderTargetView);
		SafeRelease(&m_pDepthStencil);
		SafeRelease(&m_pDepthStencilView);
		SafeRelease(&m_pShader);
		SafeRelease(&m_pVertexBuffer);
		SafeRelease(&m_pVertexLayout);
		SafeRelease(&m_pFacesIndexBuffer);

		delete pMeshGen;
	}

	/******************************************************************
	*                                                                 *
	*  DemoApp::Initialize                                            *
	*                                                                 *
	*  Create the application window and device-independent resources *
	*                                                                 *
	******************************************************************/
	HRESULT DemoApp::Initialize()
	{
		HRESULT hr;

		hr = CreateDeviceIndependentResources();
		if (SUCCEEDED(hr))
		{
			// Register the window class.
			WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
			wcex.style         = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc   = DemoApp::WndProc;
			wcex.cbClsExtra    = 0;
			wcex.cbWndExtra    = sizeof(LONG_PTR);
			wcex.hInstance     = HINST_THISCOMPONENT;
			wcex.hbrBackground = NULL;
			wcex.lpszMenuName  = NULL;
			wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
			wcex.lpszClassName = L"D3DX10DemoApp";

			RegisterClassEx(&wcex);

			// Create the application window.

			m_hwnd = CreateWindow(
				L"D3DX10DemoApp",
				L"Direct3D Demo App",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				static_cast<UINT>(640),
				static_cast<UINT>(480),
				NULL,
				NULL,
				HINST_THISCOMPONENT,
				this
				);

			hr = m_hwnd ? S_OK : E_FAIL;
			if (SUCCEEDED(hr))
			{
				m_appState.running = true;
				/*m_threadHandle = CreateThread(
				NULL,
				0,
				DemoApp::ThreadStart,
				(LPVOID)&m_appState,
				0,
				&m_threadId
				);*/

				m_timerId = SetTimer(m_hwnd, NULL, FRAME_REFRESH, NULL);

				ShowWindow(m_hwnd, SW_SHOWNORMAL);

				UpdateWindow(m_hwnd);
			}
		}

		return hr;
	}
	/******************************************************************
	*                                                                 *
	*  DemoApp::CreateDeviceIndependentResources                      *
	*                                                                 *
	*  This method is used to create resources which are not bound    *
	*  to any device. Their lifetime effectively extends for the      *
	*  duration of the app.                                           *
	*                                                                 *
	******************************************************************/

	HRESULT DemoApp::CreateDeviceIndependentResources()
	{
		return S_OK;
	}

	/******************************************************************
	*                                                                 *
	*  DXGISampleApp::CreateD3DDevice                                 *
	*                                                                 *
	******************************************************************/
	HRESULT DemoApp::CreateD3DDevice(
		IDXGIAdapter *pAdapter,
		D3D10_DRIVER_TYPE driverType,
		UINT flags,
		ID3D10Device1 **ppDevice
		)
	{
		HRESULT hr = S_OK;

		static const D3D10_FEATURE_LEVEL1 levelAttempts[] =
		{
			//D3D10_FEATURE_LEVEL_10_1,
			D3D10_FEATURE_LEVEL_10_0,
			D3D10_FEATURE_LEVEL_9_3,
			D3D10_FEATURE_LEVEL_9_2,
			D3D10_FEATURE_LEVEL_9_1,
		};

		for (UINT level = 0; level < ARRAYSIZE(levelAttempts); level++)
		{
			ID3D10Device1 *pDevice = NULL;
			hr = D3D10CreateDevice1(
				pAdapter,
				driverType,
				NULL,
				flags,
				levelAttempts[level],
				D3D10_1_SDK_VERSION,
				&pDevice
				);

			if (SUCCEEDED(hr))
			{
				// transfer reference
				*ppDevice = pDevice;
				pDevice = NULL;
				break;
			}

		}

		return hr;
	}

	/******************************************************************
	*                                                                 *
	*  DXGISampleApp::CreateD3DDeviceResources                        *
	*                                                                 *
	*  This method creates all the remaining D3D device resources     *
	*  required to render the scene. This method is called from       *
	*  CreateDeviceResources, and as such, it relies on the device    *
	*  and swap chain aleady being created.                           *
	*                                                                 *
	******************************************************************/
	HRESULT DemoApp::CreateD3DDeviceResources()
	{
		HRESULT hr = S_OK;

		// Create rasterizer state object
		{
			D3D10_RASTERIZER_DESC rsDesc;
			//rsDesc.AntialiasedLineEnable = FALSE;
			//rsDesc.CullMode = D3D10_CULL_FRONT;
			rsDesc.CullMode = D3D10_CULL_BACK;
			//rsDesc.CullMode = D3D10_CULL_NONE;
			rsDesc.DepthBias = 0;
			rsDesc.DepthBiasClamp = 0;
			rsDesc.DepthClipEnable = TRUE;
			//rsDesc.FillMode = D3D10_FILL_WIREFRAME;
			//rsDesc.FillMode = D3D10_FILL_SOLID;
			rsDesc.FillMode = pMeshGen->FillMode();
			rsDesc.FrontCounterClockwise = FALSE; // Must be FALSE for 10on9
			rsDesc.MultisampleEnable = FALSE;
			rsDesc.ScissorEnable = FALSE;
			rsDesc.SlopeScaledDepthBias = 0;

			V_RETURN( m_pDevice->CreateRasterizerState(&rsDesc, &m_pState) );
			m_pDevice->RSSetState(m_pState);
		}

		// Create Vertex Buffer
		{
			D3D10_BUFFER_DESC bd;
			bd.Usage = D3D10_USAGE_DEFAULT;
			//bd.ByteWidth = sizeof(s_VertexArray);
			bd.ByteWidth = pMeshGen->VertexArrayByteWidth();
			bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags = 0;
			D3D10_SUBRESOURCE_DATA InitData;
			//InitData.pSysMem = s_VertexArray;
			InitData.pSysMem = pMeshGen->GetVertexArray();

			V_RETURN( m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer) );

			// Set vertex buffer
			UINT stride = sizeof(SimpleVertex);
			UINT offset = 0;
			ID3D10Buffer *pVertexBuffer = m_pVertexBuffer;

			m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			m_pDevice->IASetVertexBuffers(
				0, // StartSlot
				1, // NumBuffers
				&pVertexBuffer,
				&stride,
				&offset
				);
		}

		// Create Face List Buffer
		{
			D3D10_BUFFER_DESC bd;
			bd.Usage = D3D10_USAGE_DEFAULT;
			//bd.ByteWidth = sizeof(s_FacesIndexArray);
			bd.ByteWidth = pMeshGen->FaceIndexArrayByteWidth();
			bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags = 0;
			D3D10_SUBRESOURCE_DATA InitData;
			//InitData.pSysMem = s_FacesIndexArray;
			InitData.pSysMem = pMeshGen->GetFaceIndexArray();

			V_RETURN( m_pDevice->CreateBuffer(&bd, &InitData, &m_pFacesIndexBuffer) );
		}

		// Create effect and link variables
		{
			// Load pixel shader from file
			V_RETURN( D3DX10CreateEffectFromFile(
				//L"C:\\Users\\dhood\\Downloads\\DirectX\\Code Samples\\DirectX3D\\shader.fx", NULL, NULL, 
				L"shader.fx", NULL, NULL, 
				"fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 
				m_pDevice, NULL, NULL, 
				&m_pShader, NULL, NULL ) );

			// Obtain the technique
			m_pTechniqueNoRef = m_pShader->GetTechniqueByName("Render");
			V_RETURN( m_pTechniqueNoRef ? S_OK : E_FAIL );

			// Obtain the variables
			m_pWorldVariableNoRef = m_pShader->GetVariableByName("World")->AsMatrix();
			V_RETURN( m_pWorldVariableNoRef ? S_OK : E_FAIL );

			m_pViewVariableNoRef = m_pShader->GetVariableByName("View")->AsMatrix();
			V_RETURN( m_pViewVariableNoRef ? S_OK : E_FAIL);

			// Initialize the view matrix.
			D3DXVECTOR3 Eye(0.0f, 2.0f, -6.0f);
			D3DXVECTOR3 At(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
			D3DMatrixLookAtLH(&m_ViewMatrix, &Eye, &At, &Up);
			m_pViewVariableNoRef->SetMatrix((float*)&m_ViewMatrix);

			m_pProjectionVariableNoRef = m_pShader->GetVariableByName("Projection")->AsMatrix();
			V_RETURN( m_pProjectionVariableNoRef ? S_OK : E_FAIL );

			m_pLightDir = m_pShader->GetVariableByName( "LightDir" )->AsVector();
			D3DXVECTOR3 vLightDir( 0.0f, -1.0f, -1.0f );
			V_RETURN( m_pLightDir->SetRawValue( (float*)&vLightDir, 0, sizeof( D3DXVECTOR3) ) );
		}

		// Define the input layout
		{
			//UINT numElements = ARRAYSIZE(s_InputLayout);
			UINT numElements = pMeshGen->InputLayoutArrayCount();

			// Create the input layout
			D3D10_PASS_DESC PassDesc;
			m_pTechniqueNoRef->GetPassByIndex(0)->GetDesc(&PassDesc);

			V_RETURN( m_pDevice->CreateInputLayout(
				//s_InputLayout,
				pMeshGen->GetInputLayoutArray(),
				numElements,
				PassDesc.pIAInputSignature,
				PassDesc.IAInputSignatureSize,
				&m_pVertexLayout
				) );

			// Set the input layout
			m_pDevice->IASetInputLayout(m_pVertexLayout);
		}

		return hr;
	}


	/******************************************************************
	*                                                                 *
	*  DemoApp::CreateDeviceResources                                 *
	*                                                                 *
	*  This method creates resources which are bound to a particular  *
	*  D3D device. It's all centralized here, in case the resources   *
	*  need to be recreated in case of D3D device loss (eg. display   *
	*  change, remoting, removal of video card, etc).                 *
	*                                                                 *
	******************************************************************/

	HRESULT DemoApp::CreateDeviceResources()
	{
		HRESULT hr = S_OK;

		ID3D10Device1 *pDevice = NULL;
		IDXGIDevice *pDXGIDevice = NULL;
		IDXGIAdapter *pAdapter = NULL;
		IDXGIFactory *pDXGIFactory = NULL;

		RECT rcClient;
		GetClientRect(m_hwnd, &rcClient);
		UINT nWidth = abs(rcClient.right - rcClient.left);
		UINT nHeight = abs(rcClient.bottom - rcClient.top);

		if (!m_pDevice)
		{
			// Attempt to create a new device, either Hardware or WARP
			{
				UINT nDeviceFlags = D3D10_CREATE_DEVICE_BGRA_SUPPORT;

				hr = CreateD3DDevice(
					NULL,
					D3D10_DRIVER_TYPE_HARDWARE,
					nDeviceFlags,
					&pDevice
					);

				if (FAILED(hr))
				{
					V_RETURN( CreateD3DDevice(
						NULL,
						D3D10_DRIVER_TYPE_WARP,
						nDeviceFlags,
						&pDevice
						) );
				}
			}

			// Get pointers to the various device interfaces
			V_RETURN( hr = pDevice->QueryInterface(&m_pDevice) );
			V_RETURN( hr = pDevice->QueryInterface(&pDXGIDevice) );
			V_RETURN( hr = pDXGIDevice->GetAdapter(&pAdapter) );
			V_RETURN( hr = pAdapter->GetParent(IID_PPV_ARGS(&pDXGIFactory)) );

			// Create swap chain
			{
				DXGI_SWAP_CHAIN_DESC swapDesc;
				::ZeroMemory(&swapDesc, sizeof(swapDesc));

				swapDesc.BufferDesc.Width = nWidth;
				swapDesc.BufferDesc.Height = nHeight;
				swapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
				swapDesc.BufferDesc.RefreshRate.Numerator = 60;
				swapDesc.BufferDesc.RefreshRate.Denominator = 1;
				swapDesc.SampleDesc.Count = 1;
				swapDesc.SampleDesc.Quality = 0;
				swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapDesc.BufferCount = 1;
				swapDesc.OutputWindow = m_hwnd;
				swapDesc.Windowed = TRUE;

				V_RETURN( pDXGIFactory->CreateSwapChain(m_pDevice, &swapDesc, &m_pSwapChain) );
			}

			// Create additonal resources
			V_RETURN( CreateD3DDeviceResources() );
			V_RETURN( RecreateSizedResources(nWidth, nHeight) );
		}

		return hr;
	}

	/******************************************************************
	*                                                                 *
	*  DemoApp::DiscardDeviceResources                                *
	*                                                                 *
	*  Discard device-specific resources which need to be recreated   *
	*  when a D3D device is lost                                      *
	*                                                                 *
	******************************************************************/

	void DemoApp::DiscardDeviceResources()
	{
		SafeRelease(&m_pDevice);
		SafeRelease(&m_pSwapChain);
		SafeRelease(&m_pState);

		SafeRelease(&m_pRenderTargetView);
		SafeRelease(&m_pDepthStencil);
		SafeRelease(&m_pDepthStencilView);

		SafeRelease(&m_pShader);
		SafeRelease(&m_pVertexBuffer);
		SafeRelease(&m_pVertexLayout);
		SafeRelease(&m_pFacesIndexBuffer);

		m_pDevice = NULL;
	}

#pragma endregion

#pragma region WorkerThread

	DWORD WINAPI DemoApp::ThreadStart(LPVOID lpParam)
	{
		tState* pAppState = (tState*) lpParam;

		pAppState->length = 0;

		while(pAppState->running)
		{
			//pAppState->dx++;
			//pAppState->dx = (float)((int)ceil(pAppState->dx) % 300);
			pAppState->length++;
			pAppState->length = (float)((int)ceil(pAppState->length) % 100);
			Sleep(ANIMATION_UPDATE);
		}

		return S_OK;
	}

#pragma endregion

#pragma region Message Handling

#pragma region Message Support

	/******************************************************************
	*                                                                 *
	*  DemoApp::RunMessageLoop                                        *
	*                                                                 *
	*  Main window message loop                                       *
	*                                                                 *
	******************************************************************/

	void DemoApp::RunMessageLoop()
	{
		MSG msg;

		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	/******************************************************************
	*                                                                 *
	*  DXGISampleApp::OnResize                                        *
	*                                                                 *
	*  This method is called in response to a WM_SIZE window message  *
	*                                                                 *
	*  When the window resizes, we need to resize the D3D swap chain  *
	*  and remap the corresponding D2D render target                  *
	*                                                                 *
	******************************************************************/
	void DemoApp::OnResize(UINT width, UINT height)
	{
		if (!m_pDevice)
		{
			// Recreate all device-dependent resources.
			CreateDeviceResources();
		}
		else
		{
			// Recreate only those resources that depend
			// on the window size.
			RecreateSizedResources(width, height);
		}
	}

	/******************************************************************
	*                                                                 *
	*  DXGISampleApp::OnGetMinMaxInfo                                 *
	*                                                                 *
	*  This method is called in response to a WM_GETMINMAXINFO window *
	*  message. We use it to set the minimum size of the window.      *
	*                                                                 *
	******************************************************************/

	/******************************************************************
	*                                                                 *
	*  DXGISampleApp::RecreateSizedResources                          *
	*                                                                 *
	*  This method is responsible for (re)creating all device         *
	*  resources that depend on the window size.                      *
	*                                                                 *
	******************************************************************/
	HRESULT DemoApp::RecreateSizedResources(UINT nWidth, UINT nHeight)
	{
		HRESULT hr = S_OK;
		IDXGISurface *pBackBuffer = NULL;
		ID3D10Resource *pBackBufferResource = NULL;
		ID3D10RenderTargetView *viewList[1] = {NULL};

		SafeRelease(&m_pRenderTargetView);
		m_pDevice->OMSetRenderTargets(1, viewList, NULL);

		// Resize render target buffers
		hr = m_pSwapChain->ResizeBuffers(1, nWidth, nHeight, DXGI_FORMAT_B8G8R8A8_UNORM, 0);

		if (SUCCEEDED(hr))
		{
			D3D10_TEXTURE2D_DESC texDesc;
			texDesc.ArraySize = 1;
			texDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
			texDesc.CPUAccessFlags = 0;
			texDesc.Format = DXGI_FORMAT_D16_UNORM;
			texDesc.Height = nHeight;
			texDesc.Width = nWidth;
			texDesc.MipLevels = 1;
			texDesc.MiscFlags = 0;
			texDesc.SampleDesc.Count = 1;
			texDesc.SampleDesc.Quality = 0;
			texDesc.Usage = D3D10_USAGE_DEFAULT;

			SafeRelease(&m_pDepthStencil);
			hr = m_pDevice->CreateTexture2D(&texDesc, NULL, &m_pDepthStencil);
		}


		if (SUCCEEDED(hr))
		{
			// Create the render target view and set it on the device
			hr = m_pSwapChain->GetBuffer(
				0,
				IID_PPV_ARGS(&pBackBufferResource)
				);
		}

		if (SUCCEEDED(hr))
		{
			D3D10_RENDER_TARGET_VIEW_DESC renderDesc;
			renderDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			renderDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
			renderDesc.Texture2D.MipSlice = 0;

			SafeRelease(&m_pRenderTargetView);
			hr = m_pDevice->CreateRenderTargetView(pBackBufferResource, &renderDesc, &m_pRenderTargetView);
		}


		if (SUCCEEDED(hr))
		{
			D3D10_DEPTH_STENCIL_VIEW_DESC depthViewDesc;
			depthViewDesc.Format = DXGI_FORMAT_D16_UNORM;
			depthViewDesc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
			depthViewDesc.Texture2D.MipSlice = 0;

			SafeRelease(&m_pDepthStencilView);
			hr = m_pDevice->CreateDepthStencilView(m_pDepthStencil, &depthViewDesc, &m_pDepthStencilView);
		}

		if (SUCCEEDED(hr))
		{
			viewList[0] = m_pRenderTargetView;
			m_pDevice->OMSetRenderTargets(1, viewList, m_pDepthStencilView);

			// Set a new viewport based on the new dimensions
			D3D10_VIEWPORT viewport;
			viewport.Width = nWidth;
			viewport.Height = nHeight;
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.MinDepth = 0;
			viewport.MaxDepth = 1;
			m_pDevice->RSSetViewports(1, &viewport);

			// Reset the projection matrix now that the swapchain is resized.
			D3DMatrixPerspectiveFovLH(
				&m_ProjectionMatrix,
				(float)D3DX_PI * 0.24f, // fovy
				nWidth / (float)nHeight, // aspect
				0.1f, // zn
				100.0f // zf
				);

			m_pProjectionVariableNoRef->SetMatrix((float*)&m_ProjectionMatrix);
		}

		SafeRelease(&pBackBuffer);
		SafeRelease(&pBackBufferResource);

		return hr;
	}

	void DemoApp::OnGetMinMaxInfo(MINMAXINFO *pMinMaxInfo)
	{
		pMinMaxInfo->ptMinTrackSize.x = static_cast<UINT>(200.0f);
		pMinMaxInfo->ptMinTrackSize.y = static_cast<UINT>(200.0f);
	}

	/******************************************************************
	*                                                                 *
	*  DemoApp::WndProc                                               *
	*                                                                 *
	*  Window message handler                                         *
	*                                                                 *
	******************************************************************/

	LRESULT CALLBACK DemoApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = 0;

		if (message == WM_CREATE)
		{
			LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
			DemoApp *pDemoApp = (DemoApp *)pcs->lpCreateParams;

			::SetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA,
				PtrToUlong(pDemoApp)
				);

			result = 1;
		}
		else
		{
			DemoApp *pDemoApp = reinterpret_cast<DemoApp *>(static_cast<LONG_PTR>(
				::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA
				)));

			bool wasHandled = false;

			if (pDemoApp)
			{
				switch (message)
				{
				case WM_SIZE:
					{
						UINT width = LOWORD(lParam);
						UINT height = HIWORD(lParam);
						pDemoApp->OnResize(width, height);
					}
					result = 0;
					wasHandled = true;
					break;
				case WM_GETMINMAXINFO:
					{
						MINMAXINFO *pMinMaxInfo = reinterpret_cast<MINMAXINFO *>(lParam);
						pDemoApp->OnGetMinMaxInfo(pMinMaxInfo);
					}
					result = 0;
					wasHandled = true;
					break;
				case WM_TIMER:
					{
						InvalidateRect(hwnd, NULL, false);
						//RedrawWindow(hwnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE);
					}
					result = 0;
					wasHandled = true;
					break;
				case WM_DISPLAYCHANGE:
					{
						InvalidateRect(hwnd, NULL, FALSE);
					}
					result = 0;
					wasHandled = true;
					break;
				case WM_PAINT:
					{
						pDemoApp->OnRender();

						ValidateRect(hwnd, NULL);
					}
					result = 0;
					wasHandled = true;
					break;

				case WM_MOUSEMOVE:
					{
						int xpos = LOWORD(lParam);
						int ypos = HIWORD(lParam);
						pDemoApp->m_appState.dx = (float)xpos-150;
						pDemoApp->m_appState.dy = (float)ypos-150;

						//InvalidateRect(hwnd, NULL, false);
						RedrawWindow(hwnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE);
					}
					result = 0;
					wasHandled = true;
					break;
				case WM_DESTROY:
					{
						PostQuitMessage(0);
					}
					result = 1;
					wasHandled = true;
					break;
				}
			}

			if (!wasHandled)
			{
				result = DefWindowProc(hwnd, message, wParam, lParam);
			}
		}

		return result;
	}

#pragma endregion

	/******************************************************************
	*                                                                 *
	*  DemoApp::OnRender                                              *
	*                                                                 *
	*  This method draws Direct2D content to a GDI HDC.               *
	*                                                                 *
	*  This method will automatically discard device-specific         *
	*  resources if the D3D device disappears during function         *
	*  invocation, and will recreate the resources the next time it's *
	*  invoked.                                                       *
	*                                                                 *
	******************************************************************/
	HRESULT DemoApp::OnRender()
	{
		static float t = 0.0f;
		static DWORD dwTimeStart = 0;

		HRESULT hr;

		V_RETURN( CreateDeviceResources() );

		// Calculate world rotation based on time
		{
			DWORD dwTimeCur = GetTickCount();
			if ( dwTimeStart == 0 )
			{
				dwTimeStart = dwTimeCur;
			}
			t = ( dwTimeCur - dwTimeStart) / 3000.0f;

			float a = (t * 360.0f) * ((float)D3DX_PI / 180.0f);
			D3DMatrixRotationY(&m_WorldMatrix, a);

			// Apply rotation to effect script
			m_pWorldVariableNoRef->SetMatrix((float*)&m_WorldMatrix);
		}

		
		// Render the scene
		{
			// Clear view
			float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			m_pDevice->ClearRenderTargetView( m_pRenderTargetView, ClearColor );
			m_pDevice->ClearDepthStencilView( m_pDepthStencilView, D3D10_CLEAR_DEPTH, 1, 0 );

			// Set the face list buffer
			//m_pDevice->IASetIndexBuffer(m_pFacesIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
			m_pDevice->IASetIndexBuffer(m_pFacesIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			// Apply the effect
			m_pTechniqueNoRef->GetPassByIndex(0)->Apply(0);

			// Draw the faces
			m_pDevice->DrawIndexed(
				//ARRAYSIZE(s_FacesIndexArray),
				pMeshGen->FaceIndexArrayCount(),
				0,
				0
				);

			// Swap the buffer to the screen
			hr = m_pSwapChain->Present(1, 0);

			if (hr == D2DERR_RECREATE_TARGET)
			{
				hr = S_OK;
				DiscardDeviceResources();
			}
		}

		return hr;
	}


#pragma endregion

#pragma region DirectX Draw Methods

	void DemoApp::DrawGroup()
	{


	}


#pragma endregion

#pragma endregion