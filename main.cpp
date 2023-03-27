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
#include <Window.h>

using namespace std;

void CheckHWNDWindow()
{
	HWND hwnd = GetConsoleWindow();
	if (hwnd == NULL)
	{
		cout << "GetConsoleWindow failed, GetLastError returns " << GetLastError() << endl;
	}
	else
	{
		cout << "GetConsoleWindow returned " << hwnd << endl;
	}
}


int main()
{
	DEBUG_MSG("Main.cpp : main() : starts.");

	// Create a Window and Renderer pointer
	DEBUG_MSG("Main.cpp : main() : Create a Window and Renderer pointer.");
	Window* window = nullptr;
	Renderer* renderer = nullptr;

	// Query for the user's OS
	DEBUG_MSG("Main.cpp : main() : Query for the user's OS.");
	SystemDetection::OsDetection();
	// Gets the boolean result of a function UseDirectX()
	DEBUG_MSG("Main.cpp : main() : Gets the boolean result of a function UseDirectX().");
	bool userUsesDirectX = SystemDetection().isUsingDirectX();
	// Check DirectX version
	SystemDetection detector;

	// If userGraphicsAPI is true then use DirectX, else use OpenGL
	DEBUG_MSG("Main.cpp : main() : If userGraphicsAPI is true then use DirectX, else use OpenGL.");
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

	if (!window)
	{
		cerr << "Error: failed to create window" << endl;
		return -1;
	}
	
	CheckHWNDWindow();

	HWND hwnd = window->GetHWND();

	renderer->Initialize(hwnd);

	// Initialize the DirectX 12 renderer with the window handle
	if (!renderer.Initialize(hwnd))
	{
		cerr << "Error: failed to initialize renderer" << endl;
		return -1;
	}

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