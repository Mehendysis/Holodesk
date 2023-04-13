// Window.cpp
#include "Window.h"

Window::Window(unsigned int width, unsigned int height, const std::wstring& title)
    : m_width(width), m_height(height), title_(title)
{
}

void Window::SetWindowSize(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;
}

void Window::CleanUp()
{
    this->~Window();
}

void Window::SetWidth(unsigned int width)
{
    m_width = width;
}

void Window::SetHeight(unsigned int height)
{
    m_height = height;
}
