// Renderer.h
#include "Camera.h"
#include "GLCamera.h"
#include "DX11Camera.h"
#include "GLRenderer.h"

#pragma once
template <typename GraphicsAPI>
class Renderer
{
public:
    using CameraType = typename std::conditional<std::is_same<GraphicsAPI, GLRenderer>::value, GLCamera, DX11Camera>::type;

    Renderer(int windowWidth, int windowHeight, const CameraType& camera)
        : m_camera(camera)
    {
        // implementation specific to the graphics API
        m_graphicsAPI.Initialize(windowWidth, windowHeight, camera);
    }
    void Initialize()
    {
        // implementation specific to the graphics API
        m_graphicsAPI.Initialize();
    }

    void Render()
    {
        // implementation specific to the graphics API
        m_graphicsAPI.Render();
    }

private:
    GraphicsAPI m_graphicsAPI;
    CameraType m_camera;
};