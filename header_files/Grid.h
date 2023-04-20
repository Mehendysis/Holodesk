//Grid.h
#pragma once

#include "GLMemoryWrapper.h"
//#include <windows.h>
#include <vector>

//#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "Shader.h"

class Grid {
public:
    Grid() {
        // Create grid vertices and indices
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        int numLines = 21; // 21 lines for a 20x20 grid
        float spacing = 1.0f;
        float size = spacing * (numLines - 1);

        for (int i = 0; i < numLines; ++i) {
            float offset = (i - numLines / 2) * spacing;
            vertices.push_back(-size / 2); vertices.push_back(0.0f); vertices.push_back(offset);
            vertices.push_back(size / 2); vertices.push_back(0.0f); vertices.push_back(offset);
            indices.push_back(i * 2);
            indices.push_back(i * 2 + 1);
        }

        for (int i = 0; i < numLines; ++i) {
            float offset = (i - numLines / 2) * spacing;
            vertices.push_back(offset); vertices.push_back(0.0f); vertices.push_back(-size / 2);
            vertices.push_back(offset); vertices.push_back(0.0f); vertices.push_back(size / 2);
            indices.push_back(numLines * 2 + i * 2);
            indices.push_back(numLines * 2 + i * 2 + 1);
        }

        // Create VAO, VBO, and EBO
        glGenVertexArrays(1, &m_vao);
        //glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        m_numIndices = indices.size();
    }

    //void Render(Shader& shader) {
    //    glBindVertexArray(m_vao);
    //    shader.use();
    //    glDrawElements(GL_LINES, m_numIndices, GL_UNSIGNED_INT, 0);
    //}

private:
    unsigned int m_vao, m_vbo, m_ebo;
    unsigned int m_numIndices;
};
