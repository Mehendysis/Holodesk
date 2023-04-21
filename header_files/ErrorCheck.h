//ErrorCheck.h
#pragma once

#include "GLMemoryWrapper.h"

#include <glm/mat4x4.hpp>

class GLShaderProgram;

void check_frame_buffer(GLuint framebufferObject);

void check_frame_buffer_additonal_message(GLuint framebufferObject);

bool check_aspect_ratio_error(const glm::mat4& projection_matrix);

void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

bool ShadersCompiled(const GLShaderProgram& shaderProgram);

