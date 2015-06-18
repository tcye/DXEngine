#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "Director.h"

static char szTitle[] = "GameEngine";
static char szWindowClass[] = "GameEngineWndClass";

bool Game::Init(bool fullscreen, int width, int height)
{
	m_fullscreen = fullscreen;
	m_width = width;
	m_height = height;

	if (!InitWindow())
		return false;

	if (!InitDirectX())
		return false;

	if (!theDirector->Init())
		return false;

	if (!theInput->Init())
		return false;

	return true;
}

void Game::Run()
{
	MSG msg;
	bool done;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			theInput->RefreshInputState();
			theTime->RefreshTimeStateBeforeFrame();
			theDirector->Update();
			theDirector->Render();
			theTime->RefreshTimeStateAfterFrame();
		}
	}
}

void Game::Cleanup()
{
	theInput->Cleanup();
	theDirector->Cleanup();

	m_device->Release();
	m_device = nullptr;

	m_d3d->Release();
	m_d3d = nullptr;

	DestroyWindow(m_hwnd);
	m_hwnd = nullptr;

	UnregisterClass(szWindowClass, m_hinstance);
	m_hinstance = nullptr;
}

bool Game::InitWindow()
{
	m_hinstance = GetModuleHandle(NULL);

	WNDCLASSEX wcex;

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hinstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wcex);

	DWORD dwStyle = WS_VISIBLE;
	if (m_fullscreen)
		dwStyle |= WS_POPUP;
	else
		dwStyle |= WS_OVERLAPPEDWINDOW;

	m_hwnd = CreateWindow(szWindowClass, szTitle, dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height, 
		NULL, NULL, m_hinstance, NULL);

	if (!m_hwnd)
		return false;

	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	return true;
}

bool Game::InitDirectX()
{
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_d3d)
		return false;

	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = m_width;
	d3dpp.BackBufferHeight = m_height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = m_hwnd;
	d3dpp.Windowed = !m_fullscreen;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr = m_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		d3dpp.hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_device);

	if (FAILED(hr))
		return false;

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) 
			PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}