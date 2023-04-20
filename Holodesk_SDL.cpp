//Holodesk_SDL.cpp

#include "Holodesk_SDL.h"
#include "Debug.h"
#include "ErrorCheck.h"
#include "Window.h"
#include "GLWindow.h"
#include "GLMemoryWrapper.h"

#include <string>
#include <SDL2/SDL_image.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <codecvt>

SDL_Window* initialize_sdl_and_opengl()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : initialize_sdl_and_opengl() : Error below.");
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to initialize SDL.");
    }

    // Create an OpenGL context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // set OpenGL context version to 4.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    Window initialWindow;
    std::wstring wTitle = initialWindow.GetHoloWinTitle();
    int len = WideCharToMultiByte(CP_UTF8, 0, wTitle.c_str(), -1, NULL, 0, NULL, NULL);
    std::string title(len, 0);
    WideCharToMultiByte(CP_UTF8, 0, wTitle.c_str(), -1, &title[0], len, NULL, NULL);


    //bool fullscreen = window.getDefaultFullscreen();
    int width = initialWindow.GetInitialWidth();
    int height = initialWindow.GetInitialHeight();

    // Create an SDL window
    SDL_Window* sdlWindow = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL);

    if (!sdlWindow)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : initialize_sdl_and_opengl() : Error below.");
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to create SDL window.");
    }

    SDL_GLContext context = SDL_GL_CreateContext(sdlWindow);
    if (!context)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : initialize_sdl_and_opengl() : Error below.");
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(sdlWindow);
        throw std::runtime_error("Failed to create OpenGL context.");
    }

    // Load OpenGL functions using GLAD
    if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0)
    {
        DEBUG_MSG("¢RErrorCheck.cpp : initialize_sdl_and_opengl() : Error below.");
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(sdlWindow);
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    // Set swap interval to synchronize with the vertical retrace
    SDL_GL_SetSwapInterval(1);

    glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    if (check_aspect_ratio_error(projection_matrix))
    {
        DEBUG_MSG("¢RErrorCheck.cpp : initialize_sdl_and_opengl() : Error Quit.");
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(sdlWindow);
        throw std::runtime_error("Aspect ratio error.");
    }

    return sdlWindow;
}

SDL_Window* createSDLWindow(const char* title, int width, int height)
{
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "SDL Error: Failed to create window - " << SDL_GetError() << std::endl;
        return NULL;
    }
    return window;
}

bool checkSDLError()
{
    const char* error = SDL_GetError();
    if (*error != '\0')
    {
        std::cout << "SDL Error: " << error << std::endl;
        SDL_ClearError();
        return true;
    }
    return false;
}

SDL_GLContext createSDLGLContext(SDL_Window* window)
{
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == NULL)
    {
        std::cout << "SDL Error: Failed to create OpenGL context - " << SDL_GetError() << std::endl;
        return NULL;
    }
    return context;
}

SDL_Surface* loadSDLImage(const char* filepath)
{
    SDL_Surface* surface = IMG_Load(filepath);
    if (surface == NULL)
    {
        std::cout << "SDL Error: Failed to load image - " << IMG_GetError() << std::endl;
        return NULL;
    }
    return surface;
}
