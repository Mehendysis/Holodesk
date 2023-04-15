// DX11Window.cpp
#include "DX11Window.h"
#include <codecvt>

DX11Window::DX11Window(unsigned int width, unsigned int height, const std::wstring& title)
    : Window(width, height, title)
{
    Create();
}

DX11Window::~DX11Window()
{
    Close();
}

bool DX11Window::Create()
{
    m_hInstance = GetModuleHandle(NULL);
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = m_hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = L"DX11WindowClass";

    if (!RegisterClassExW(&wcex))
    {
        MessageBox(NULL, TEXT("Failed to register window class"), TEXT("Error"), MB_OK | MB_ICONERROR);

        return false;
    }

    m_windowHandle = CreateWindowExW( // Use CreateWindowExW
        0,
        L"DX11WindowClass",
        title_.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        m_width, m_height,
        NULL, NULL,
        m_hInstance,
        NULL);

    if (!m_windowHandle)
    {
        MessageBox(NULL, TEXT("Failed to create window"), TEXT("Error"), MB_OK | MB_ICONERROR);
        return false;
    }

    ShowWindow(m_windowHandle, SW_SHOW);
    UpdateWindow(m_windowHandle);
    return true;
}

LRESULT CALLBACK DX11Window::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) 
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

bool DX11Window::ProcessEvents()
{
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return !m_shouldClose;
}

void DX11Window::Close()
{
    // Close the window
}

void* DX11Window::GetNativeWindowHandle() const
{
    return static_cast<void*>(m_windowHandle);
}

HWND DX11Window::GetWindowHandle() const
{
    return m_windowHandle;
}