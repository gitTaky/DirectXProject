cbuffer mycBuffer : register(b0)
{
    float4x4 wpvMatrix;
    float4x4 worldMatrix;
}; 

struct VS_INPUT
{
    float3 inPos : POSITION;
    float2 inTexCoord : TEXCOORD;
    float3 inNormal : NORMAL;
};

struct VS_OUTPUT
{
    float4 outPosition : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
    float3 outNormal : NORMAL;
    float4 outWorldPosition : WORLD_POSITION;
};

VS_OUTPUT main(VS_INPUT input) 
{
    VS_OUTPUT output;
    output.outPosition = mul(float4(input.inPos, 1.0f), wpvMatrix);
    output.outTexCoord = input.inTexCoord;
    output.outNormal = normalize(mul(float4(input.inNormal, 0.f), worldMatrix));
    output.outWorldPosition = mul(float4(input.inPos, 1.0f), worldMatrix);
    return output;
}