#include <iostream>
#include <string>
#include "SystemDetection.h"

using namespace std;

int main()
{
	// Get the boolean result of a function UseDirectX()
	bool userUsesDirectX = SystemDetection().isUsingDirectX();

	// If userGraphicsAPI is true then use DirectX, else use OpenGL
	if (userUsesDirectX)
	{
		// Initialize DirectX

	}
	else
	{
		// Use OpenGL

	}
}