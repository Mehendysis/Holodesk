//main.cpp

//#define SDL_MAIN_HANDLED
//
//#include "GLRenderer.h"
//#include "GLWindow.h"
//#include "Debug.h"
//#include "ErrorCheck.h"
//#include "SystemDetection.h"
//#include "GLUI.h"
//#include "UI.h"
//#include "Renderer.h"
//#include "Window.h"
//#include "DX11Renderer.h"
//#include "DX11Camera.h"
//#include "DX11Window.h"
//#include "TypeConversion.h"
//#include "Holodesk_SDL.h"
//
//#include <filesystem>
//#include "imgui.h"
//#include "imgui_impl_sdl2.h"
//#include <SDL.h>
//#include <iostream>
//#include <utility>



//unsigned short int windowWidth = initialWindow.GetInitialWidth();
//unsigned short int windowHeight = initialWindow.GetInitialHeight();
//std::wstring

//SDL_Window* initialize_sdl_and_opengl();

//void InitOpenGL(unsigned short int windowWidth, unsigned short int windowHeight, std::wstring windowTitle);
//bool IsGLInitialized();
//void InitDirectX();
//void CleanUp();


#include "Window.h"
#include "Debug.h"

#include <imgui.h>
#include "GLHolodeskMain.h"
#include "DXHolodeskMain.h"
#include "SystemDetection.h"

using namespace std;

int main(int argc, char* argv[])
{
    DEBUG_MSG("¢BMain.cpp : main() : starts.");

    // Check if the user can run DirectX
    //int dxVersion = SystemDetection::GetDirectXVersion();
    //bool canRunDirectX = dxVersion >= 11;

    // Parse command-line arguments
    string renderer;
    renderer = "opengl";
    //if (argc >= 2)
    //{
    //    renderer = argv[1];
    //}
    //else
    //{
    //    // Choose the renderer based on the user's system capabilities
    //    renderer = canRunDirectX ? "directx" : "opengl";
    //}

    if (renderer == "opengl") 
    {
        InitalizeHolodeskOpenGL(argc, argv);
    }
    else if (renderer == "directx") 
    {
        InitalizeHolodeskDirectX();
    }
    else 
    {
        DEBUG_MSG("Main.cpp : main() : Usage: ");
        cout << argv[0] << " [opengl|directx]\n" << endl;
        return 1;
    }

    //CleanUp();
    return 0;
}

//void CleanUp()
//{
//    // Clean up
//    DEBUG_MSG("Main.cpp : main() : Clean up.");
//}