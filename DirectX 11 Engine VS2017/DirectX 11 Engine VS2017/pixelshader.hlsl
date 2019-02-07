cbuffer lightBuffer : register(b0)
{
    float3  ambientLightColor;
    float   ambientLightStrength;
}

cbuffer dlightBuffer : register(b1)
{
    float3 dynamicLightColor;
    float dynamicLightStrenght;
    float3 dynamicLightPosition;
}

struct PS_INPUT
{
    float4 inPosition : SV_POSITION;
    float2 inTexCoord : TEXCOORD;
    float3 inNormal : NORMAL;
    float4 worldPosition : WORLD_POSITION;
};

Texture2D objTexture : TEXTURE : register(t0);
SamplerState objSamplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 sampleColor = objTexture.Sample(objSamplerState, input.inTexCoord);

    float3 ambientLight = ambientLightColor * ambientLightStrength;
    float3 appliedLight = ambientLight;

    float3 vectorToLight = normalize(dynamicLightPosition - (float3) input.worldPosition);
    float diffuseLightIntensity = max(dot(vectorToLight, input.inNormal), 0);
    float3 diffuseLight = diffuseLightIntensity * dynamicLightStrenght * dynamicLightColor;
    
    appliedLight += diffuseLight;

    float3 finalColor = saturate(sampleColor * appliedLight);
    return float4(finalColor, 1.f);
}