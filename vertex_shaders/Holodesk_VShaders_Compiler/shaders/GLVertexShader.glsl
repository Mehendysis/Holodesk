// GLSL file Vertex shader ready for compilation,
// its content is for OpenGL 4.6
// for a voxel game engine editor using Imgui and Dear Imgui OpenGL backend (imgui_impl_opengl3.cpp)

// Set the GLSL version
#version 460 core

// Declare uniform variables (in this case, the model-view-projection matrix)
uniform mat4 uModelViewProjectionMatrix;

// Declare input attributes (vertex position, texture coordinates, and vertex color)
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec4 aColor;

// Declare output variables to pass data to the fragment shader
out vec2 vUV;
out vec4 vColor;

// The main function of the vertex shader
void main()
{
    // Calculate the clip-space position
    gl_Position = uModelViewProjectionMatrix * vec4(aPosition, 1.0f);
    
    // Pass through the texture coordinates and vertex color to the fragment shader
    vUV = aUV;
    vColor = aColor;
}