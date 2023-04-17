// Window.cpp
#pragma once
#include <string>

class Window
{
public:
	const unsigned short int GetInitialWidth() const {return m_InitialWidth;}
	const unsigned short int GetInitialHeight() const { return m_InitialHeight; }
	const std::wstring GetHoloWinTitle() const { return m_HolowdestWindowTitle; }

private:
	const unsigned short int m_InitialWidth = 800;
	const unsigned short int m_InitialHeight = 600;
	const std::wstring m_HolowdestWindowTitle = L"Holodesk";
};