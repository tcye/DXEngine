#pragma once

class Game : public Singleton<Game>
{
public:
	bool Init(bool fullscreen, int width, int height);
	void Run();
	void Cleanup();

	IDirect3DDevice9* GetDeviceHandle()
	{
		return m_device;
	}

	HWND GetWindowHandle()
	{
		return m_hwnd;
	}

protected:
	bool InitWindow();
	bool InitDirectX();

private:
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	IDirect3D9* m_d3d;
	IDirect3DDevice9* m_device;

	bool m_fullscreen;
	int m_width;
	int m_height;
};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);