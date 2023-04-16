//ErrorCheck.h
#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <SDL.h>

void check_frame_buffer(GLuint framebufferObject);

void check_frame_buffer_additonal_message(GLuint framebufferObject);

bool check_aspect_ratio_error(const glm::mat4& projection_matrix);

bool initialize_sdl_and_opengl(SDL_Window*& window, SDL_GLContext& context);

void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

bool checkSDLError();

SDL_Window* createSDLWindow(const char* title, int width, int height);

SDL_GLContext createSDLGLContext(SDL_Window* window);

SDL_Surface* loadSDLImage(const char* filepath);

