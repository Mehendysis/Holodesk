// DirectXWindow.cpp
#include "DirectXWindow.h"

DirectXWindow::DirectXWindow(unsigned int width, unsigned int height, const std::wstring& title)
    : Window(width, height, title) 
{
    Create();
}

DirectXWindow::~DirectXWindow()
{
    Close();
}

void DirectXWindow::Create()
{
    m_hInstance = GetModuleHandle(NULL);

    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = m_hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = L"DirectXWindowClass";

    if (!RegisterClassEx(&wcex)) 
    {
        MessageBox(NULL, TEXT("Failed to register window class"), TEXT("Error"), MB_OK | MB_ICONERROR);

        return;
    }

    m_windowHandle = CreateWindowEx(
        0,
        L"DirectXWindowClass", // Use wide string literal (L)
        title_.c_str(), // Convert std::string to LPCWSTR
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width_, height_,
        nullptr, nullptr, m_hInstance, nullptr);

    if (!m_windowHandle) 
    {
        MessageBox(NULL, TEXT("Failed to create window"), TEXT("Error"), MB_OK | MB_ICONERROR);
        return;
    }

    ShowWindow(m_windowHandle, SW_SHOW);
    UpdateWindow(m_windowHandle);
}

LRESULT CALLBACK DirectXWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

bool DirectXWindow::ProcessEvents()
{
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return !m_shouldClose;
}


void DirectXWindow::Close() 
{
    // Close the window
}

void* DirectXWindow::GetNativeWindowHandle() const 
{
    return static_cast<void*>(m_windowHandle);
}

HWND DirectXWindow::GetWindowHandle() const
{
    return m_windowHandle;
}