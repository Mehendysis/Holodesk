// Window.h
#pragma once
#include <Windows.h>
#include <string>

using namespace std;

class Window {
public:
    Window(unsigned int width, unsigned int height, const std::wstring& title); // Updated to std::wstring
    virtual ~Window() {}

    virtual void Create() = 0;
    virtual bool ProcessEvents() = 0;
    virtual void Close() = 0;


    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    virtual HWND GetWindowHandle() const = 0;
    virtual void* GetNativeWindowHandle() const = 0;

protected:
    unsigned int width_;
    unsigned int height_;
    wstring title_;
};
