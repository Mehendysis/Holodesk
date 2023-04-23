// GLHolodeskMain.h
#pragma once
//#include <string>
#define SDL_MAIN_HANDLED
#include <SDL.h>


void InitalizeHolodeskOpenGL(int argc, char* argv[]);

int SDL_main(int argc, char* argv[]);

void InitalizeSDL();

void IsSDLInitialized(SDL_Window* sdlWindow);

SDL_GLContext CreateSDLGLContext(SDL_Window* sdlWindow);

void InitializeGlad();