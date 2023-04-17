// UI.h

#pragma once
#ifndef UI_H
#define UI_H

#include "Window.h"

#include "Camera.h"

class UI {
public:
    UI(Window* windowPtr);
    ~UI();

private:
    Window* m_windowPtr;
};

#endif // UI_H
