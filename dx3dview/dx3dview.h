#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER              // Allow use of features specific to Windows 7 or later.
#define WINVER 0x0700       // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT        // Allow use of features specific to Windows 7 or later.
#define _WIN32_WINNT 0x0700 // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d3d10_1.h>
#include <D3DX10math.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#include <fstream>

#include "d3dmath.h"
#include "MeshGen.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "TorusMesh.h"


#define IDR_PIXEL_SHADER 100

#ifndef V_RETURN
#define V_RETURN(x)    { hr = (x); if( FAILED(hr) ) { return hr; } }
#endif

/******************************************************************
*                                                                 *
*  Macros                                                         *
*                                                                 *
******************************************************************/

template<class Interface>
inline void
SafeRelease(
    Interface **ppInterfaceToRelease
    )
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = NULL;
    }
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

/* Constants */
#ifndef FRAME_REFRESH
#define FRAME_REFRESH 33
#endif

#ifndef ANIMATION_UPDATE
#define ANIMATION_UPDATE 15
#endif

/******************************************************************
*                                                                 *
*  DemoApp                                                        *
*                                                                 *
******************************************************************/

typedef struct
{
	bool running;
	float dx;
	float dy;
	float length;
} tState;


class DemoApp
{
public:
    DemoApp();
    ~DemoApp();

    HRESULT Initialize();

    void RunMessageLoop();

private:
    HRESULT CreateDeviceIndependentResources();
    HRESULT CreateDeviceResources();
	HRESULT RecreateSizedResources(UINT nWidth, UINT nHeight);

	HRESULT CreateD3DDevice(
		IDXGIAdapter *pAdapter,
		D3D10_DRIVER_TYPE driverType,
		UINT flags,
		ID3D10Device1 **ppDevice
		);

	HRESULT CreateD3DDeviceResources();
    void DiscardDeviceResources();

	HRESULT LoadResourceShader(
		ID3D10Device *pDevice,
		ID3D10Effect **ppShader);

    HRESULT OnRender();
	void OnResize(UINT width, UINT height);
	void OnGetMinMaxInfo(MINMAXINFO *pMinMaxInfo);

	void DrawGroup();
	void DrawCube();
	
    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
        );

	static DWORD WINAPI ThreadStart(LPVOID lpParameter);

private:
    HWND m_hwnd;

	UINT_PTR m_timerId;
	HANDLE m_threadHandle;	
	DWORD m_threadId;

	tState m_appState;

	IDXGISwapChain* m_pSwapChain;
	ID3D10Device* m_pDevice;
	ID3D10RasterizerState *m_pState;

	MeshGen* pMeshGen;

	ID3D10Buffer *m_pVertexBuffer;
    ID3D10InputLayout *m_pVertexLayout;
	ID3D10Buffer *m_pFacesIndexBuffer;

	ID3D10Effect *m_pShader;
	ID3D10EffectTechnique *m_pTechniqueNoRef;
    ID3D10EffectMatrixVariable *m_pWorldVariableNoRef;
    ID3D10EffectMatrixVariable *m_pViewVariableNoRef;
	ID3D10EffectMatrixVariable *m_pProjectionVariableNoRef;
    ID3D10EffectVectorVariable *m_pLightDir;


	ID3D10RenderTargetView *m_pRenderTargetView;
	ID3D10Texture2D *m_pDepthStencil;
	ID3D10DepthStencilView *m_pDepthStencilView;

	D3DXMATRIX m_WorldMatrix;
    D3DXMATRIX m_ViewMatrix;
    D3DXMATRIX m_ProjectionMatrix;

	//static const SimpleVertex s_VertexArray[];
	//static const SHORT DemoApp::s_FacesIndexArray[];
	//static const D3D10_INPUT_ELEMENT_DESC s_InputLayout[];
};
