//main.cpp
#include <SystemDetection.h>
#include <OpenGLRenderer.h>
#include <DirectXRenderer.h>
#include <OpenGLWindow.h>
#include <DirectXWindow.h>
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
	if (userUsesDirectX)
	{
		DEBUG_MSG("Main.cpp : main() : Initialize DirectX.");
		window = new DirectXWindow(800, 600, L"Holodesk");
		renderer = new DirectXRenderer(*window);
	}
	else
	{
		DEBUG_MSG("Main.cpp : main() : Initialize OpenGL.");
		window = new OpenGLWindow(800, 600, L"Holodesk");
		renderer = new OpenGLRenderer(*window);
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
	delete renderer;
	delete window;
}