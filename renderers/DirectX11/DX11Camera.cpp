//DX11Camera.cpp

#include "DX11Camera.h"

#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace DirectX;
using namespace DirectX::PackedVector;


DX11Camera::DX11Camera()
{
    // Initialize default camera position and orientation
    m_position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_up = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    m_lookAt = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);

    // Calculate initial view matrix
    UpdateViewMatrix();
}

void DX11Camera::UpdateViewMatrix()
{
    // Calculate camera direction
    DirectX::XMFLOAT3 direction(0.0f, 0.0f, 1.0f);
    DirectX::XMVECTOR rotationQuaternion = DirectX::XMQuaternionRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
    DirectX::XMVECTOR directionVector = DirectX::XMVector3Rotate(DirectX::XMLoadFloat3(&direction), rotationQuaternion);
    DirectX::XMStoreFloat3(&m_lookAt, directionVector);

    // Calculate up direction
    DirectX::XMFLOAT3 up(0.0f, 1.0f, 0.0f);
    DirectX::XMVECTOR upVector = DirectX::XMVector3Rotate(DirectX::XMLoadFloat3(&up), rotationQuaternion);
    DirectX::XMStoreFloat3(&m_up, upVector);

    // Calculate view matrix
    DirectX::XMVECTOR positionVector = DirectX::XMLoadFloat3(&m_position);
    DirectX::XMVECTOR lookAtVector = DirectX::XMLoadFloat3(&m_lookAt);
    DirectX::XMVECTOR upVector2 = DirectX::XMLoadFloat3(&m_up);
    DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(positionVector, lookAtVector, upVector2);
    DirectX::XMFLOAT4X4 viewMatrixFloat4x4;
    DirectX::XMStoreFloat4x4(&viewMatrixFloat4x4, viewMatrix);
    m_viewMatrix = DirectX::XMLoadFloat4x4(&viewMatrixFloat4x4);
}

void DX11Camera::SetPosition(float x, float y, float z)
{
    m_position = DirectX::XMFLOAT3(x, y, z);
    m_viewDirty = true;
}

void DX11Camera::SetLookAt(float x, float y, float z)
{
    m_lookAt.x = x;
    m_lookAt.y = y;
    m_lookAt.z = z;

    // Calculate the new view matrix
    XMVECTOR eye = XMLoadFloat3(&m_position);
    XMVECTOR target = XMLoadFloat3(&m_lookAt);
    XMVECTOR up = XMLoadFloat3(&m_upVector);

    m_viewMatrix = XMMatrixLookAtLH(eye, target, up);

    m_viewDirty = true;
}

void DX11Camera::SetUp(float x, float y, float z)
{
    m_up = DirectX::XMFLOAT3(x, y, z);
    m_viewDirty = true;
}

void DX11Camera::SetProjection(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
    // Convert the field of view angle from degrees to radians
    float fovRadians = XMConvertToRadians(fovDegrees);

    // Calculate the projection matrix using DirectXMath functions
    m_projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);

    // Set the view dirty flag to true so that the view matrix is recalculated
    m_viewDirty = true;
}

void DX11Camera::operator=(const DirectX::XMMATRIX& matrix)
{
    m_viewMatrix = matrix;
}

