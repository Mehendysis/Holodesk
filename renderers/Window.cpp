// Window.cpp
#include "Window.h"

Window::Window(unsigned int width, unsigned int height, const std::wstring& title)
    : width_(width), height_(height), title_(title) {
}

unsigned int Window::GetWidth() const {
    return width_;
}

unsigned int Window::GetHeight() const {
    return height_;
}
