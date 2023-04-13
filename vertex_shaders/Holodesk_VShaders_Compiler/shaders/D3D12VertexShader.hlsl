// HLSL file Vertex shader ready for compilation,
// its content is for d3d directx 12
// for a voxel game engine editor using Imgui and ImGuiDX12 as ui and font
// Path: shaders\D3D12VertexShader.hlsl

// Include ImGui header
//#include "ImGui/imgui.h"

// Declare a constant buffer to store the model-view-projection matrix
cbuffer VertexConstantBuffer : register(b0)
{
	float4x4 ModelViewProjectionMatrix;
};

// Define the input structure for the vertex shader
struct VertexInput
{
	float3 Position : POSITION; // Vertex position
	float2 UV : TEXCOORD0;      // Texture coordinates
	float4 Color : COLOR0;      // Vertex color
};

// Define the output structure for the vertex shader
struct VertexOutput
{
	float2 UV : TEXCOORD0;      // Texture coordinates
	float4 Color : COLOR0;      // Vertex color
	float4 Position : SV_POSITION; // Screen-space position (output)
};

// The main function of the vertex shader
VertexOutput main(VertexInput input)
{
	VertexOutput output;
	// Calculate the screen-space position
	output.Position = mul(float4(input.Position, 1.0f), ModelViewProjectionMatrix);
	output.UV = input.UV;       // Pass through the texture coordinates
	output.Color = input.Color; // Pass through the vertex color
	return output;
}
