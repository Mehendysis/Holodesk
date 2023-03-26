//main.cpp
#include <SystemDetection.h>
#include <OpenGLRenderer.h>
#include <DirectX12Renderer.h>
#include <DirectX11Renderer.h>
#include <OpenGLWindow.h>
#include <DirectX12Window.h>
#include <DirectX11Window.h>
#include <Renderer.h>
#include <Debug.h>

using namespace std;

int main()
{
	DEBUG_MSG("Main.cpp : main() : starts.");

	// Query for the user's OS
	DEBUG_MSG("Main.cpp : main() : Query for the user's OS.");
	SystemDetection::OsDetection();

	// Gets the boolean result of a function UseDirectX()
	DEBUG_MSG("Main.cpp : main() : Gets the boolean result of a function UseDirectX().");
	bool userUsesDirectX = SystemDetection().isUsingDirectX();

	// Create a Window and Renderer pointer
	DEBUG_MSG("Main.cpp : main() : Create a Window and Renderer pointer.");
	Window* window = nullptr;

	Renderer* renderer = nullptr;

	// If userGraphicsAPI is true then use DirectX, else use OpenGL
	DEBUG_MSG("Main.cpp : main() : If userGraphicsAPI is true then use DirectX, else use OpenGL.");

	// Check DirectX version
	SystemDetection detector;

	if (userUsesDirectX)
	{
		// Check DirectX version
		if (detector.GetDirectXVersion() >= 12)
		{
			DEBUG_MSG("Main.cpp : main() : Initialize DirectX 12.");
			window = new DirectX12Window(800, 600, L"Holodesk");
			renderer = new DirectX12Renderer(*window);
		}
		else
		{
			DEBUG_MSG("Main.cpp : main() : Initialize DirectX 11.");
			window = new DirectX11Window(800, 600, L"Holodesk");
			renderer = new DirectX11Renderer(*window);
		}
	}

	renderer->Initialize();

	DEBUG_MSG("Main.cpp : main() : Enters main loop.");
	while (window->ProcessEvents())
	{

		DEBUG_MSG("Main.cpp : main() : Render the scene.");
		// Render the scene
		renderer->Render();

	}
	// Clean up
	DEBUG_MSG("Main.cpp : main() : Out of while loop for Clean up.");
	delete renderer;
	delete window;

	DEBUG_MSG("Main.cpp : main() : End of Clean up.");
}