//DX11Camera.h
#pragma once

#include <DirectXMath.h>

class DX11Camera
{
public:
    DX11Camera();

    void UpdateViewMatrix();

    void SetPosition(float x, float y, float z);
    void SetLookAt(float x, float y, float z);
    void SetUp(float x, float y, float z);
    void SetProjection(float fovDegrees, float aspectRatio, float nearZ, float farZ);
    void operator=(const DirectX::XMMATRIX& matrix);

    const DirectX::XMFLOAT3& GetPosition() const { return m_position; }
    const DirectX::XMFLOAT3& GetLookAt() const { return m_lookAt; }
    const DirectX::XMFLOAT3& GetUp() const { return m_up; }
    const DirectX::XMMATRIX& GetViewMatrix() const { return m_viewMatrix; }
    const DirectX::XMMATRIX& GetProjectionMatrix() const { return m_projectionMatrix; }

private:
    bool m_viewDirty;
    DirectX::XMFLOAT3 m_upVector;
    DirectX::XMFLOAT3 m_position;
    DirectX::XMFLOAT3 m_rotation;
    DirectX::XMFLOAT3 m_lookAt;
    DirectX::XMFLOAT3 m_up;
    DirectX::XMMATRIX m_projectionMatrix;
    DirectX::XMMATRIX m_viewMatrix;
};
