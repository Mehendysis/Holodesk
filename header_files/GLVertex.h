//GLVertex.h
#pragma once
#ifndef GL_VERTEX_H
#define GL_VERTEX_H

#include <glm/glm.hpp>

struct GLVertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

#endif
