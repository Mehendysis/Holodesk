// OpenGLWindow.cpp
#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow(unsigned int width, unsigned int height, const std::wstring& title)
    : Window(width, height, title) 
{
}

OpenGLWindow::~OpenGLWindow()
{
    Close();
}

void OpenGLWindow::Create()
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
    wcex.lpszClassName = TEXT("HolodeskWindowClass");

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, TEXT("Failed to register window class"), TEXT("Error"), MB_OK | MB_ICONERROR);
        return;
    }

    m_windowHandle = CreateWindowEx(
        0,
        L"OpenGLWindowClass", // Use wide string literal (L)
        title_.c_str(), // Convert std::string to LPCWSTR
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width_, height_,
        nullptr, nullptr, GetModuleHandle(nullptr), nullptr);


    if (!m_windowHandle) {
        MessageBox(NULL, TEXT("Failed to create window"), TEXT("Error"), MB_OK | MB_ICONERROR);
        return;
    }

    ShowWindow(m_windowHandle, SW_SHOW);
    UpdateWindow(m_windowHandle);
}

LRESULT CALLBACK OpenGLWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

bool OpenGLWindow::ProcessEvents() {
    // Process window events and return true if the window is still open, false otherwise
    return true;
}

void OpenGLWindow::Close() {
    // Close the window
}

void* OpenGLWindow::GetNativeWindowHandle() const 
{
    return static_cast<void*>(m_windowHandle);
}

HWND OpenGLWindow::GetWindowHandle() const
{
    return m_windowHandle;
}
