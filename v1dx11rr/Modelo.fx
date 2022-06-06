Texture2D colorMap : register(t0);
Texture2D specMap : register(t1);

SamplerState colorSampler : register(s0);

cbuffer cbChangerEveryFrame : register(b0)
{
	matrix worldMatrix;
};

cbuffer cbNeverChanges : register(b1)
{
	matrix viewMatrix;
};

cbuffer cbChangeOnResize : register(b2)
{
	matrix projMatrix;
};

cbuffer cbChangesOccasionally : register(b3)
{
	float3 cameraPos;
};

cbuffer cbChangesOccasionally : register(b4)
{
	float specForce;
};

struct VS_Input
{
	float4 pos : POSITION;
	float2 tex0 : TEXCOORD0;	
	float3 normal : NORMAL0;
};

struct PS_Input
{
	float4 pos : SV_POSITION;
	float2 tex0 : TEXCOORD0;	
	float3 normal : TEXCOORD1;
	float3 campos : TEXCOORD2;
	float specForce : TEXCOORD3;
    float fogFactor : FOG;
};

PS_Input VS_Main(VS_Input vertex)
{
	
	float4 worldPosition;
    float4 posVertex;

		PS_Input vsOut = (PS_Input)0;

		vsOut.pos = mul(vertex.pos, worldMatrix);
		vsOut.pos = mul(vsOut.pos, viewMatrix);
		 posVertex = vsOut.pos;
		vsOut.pos = mul(vsOut.pos, projMatrix);

		vsOut.tex0 = vertex.tex0;
		vsOut.normal = normalize(mul(vertex.normal, worldMatrix));

		worldPosition = mul(vertex.pos, worldMatrix);

		vsOut.campos = cameraPos.xyz - worldPosition.xyz;

		vsOut.campos = normalize(vsOut.campos);

		vsOut.specForce = specForce;
	
	//NIEBLA LINEAL
    float fogStart = -800.0f;
    float fogEnd = 800.0f;
	
    float fogFactor;
    fogFactor = saturate((fogEnd - posVertex.z) / (fogEnd - fogStart));
    vsOut.fogFactor = fogFactor;

	return vsOut;
}

float4 PS_Main(PS_Input pix) : SV_TARGET
{
	float4 textureColor;
	float3 lightDir;
	float lightIntensity;
	float4 color;
	float3 reflection;
	float4 specular;
	float4 specularMap;
	float4 finalSpec;

	textureColor = colorMap.Sample(colorSampler, pix.tex0);
	color = float4(0.2, 0.2, 0.2, 1);// ambient color

	specular = float4(0.0, 0.0, 0.0, 1.0); //specular color
	specularMap = specMap.Sample(colorSampler, pix.tex0);

	lightDir = -(float3(0.5f, -1.0f, 0.0f)); // lightDirection

	lightIntensity = saturate(dot(pix.normal, lightDir));

	if (lightIntensity > 0) {
		// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
		color += (float4(1.0f, 1.f, 1.f, 1.0f)/*diffuse color*/ * lightIntensity);

		// Saturate the ambient and diffuse color.
		color = saturate(color);

		// Calculate the reflection vector based on the light intensity, normal vector, and light direction.
		reflection = normalize(2 * lightIntensity * pix.normal - lightDir);

		// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
		specular = pow(saturate(dot(reflection, pix.campos)), pix.specForce);
		finalSpec = specular * specularMap;
	}
	
	//float fogAmount = saturate((distToEye - gFogStart) / gFogRange);
 //   litcolor = lerp(litcolor, gFogColor, fogAmount);
	
 //   float distToEye = length(reflection);
 //   float fogamount = saturate((distToEye - 0.0f) / 100.0f);
 //   color = lerp(color, float4(0.3f, 0.3f, 0.3f, 1.0)fogAmount);
	
 //   return floar4(color.x, color.y, color.z, 0.8);
	
	//Set the color of the fog to grey
    float4 fogColor = float4(0.5f, 0.5f, 0.5f, 0.1f);
	
	//Fog
    color = pix.fogFactor * color * textureColor + (1.0f - pix.fogFactor) * fogColor;
	//color = color * textureColor;

	color = saturate(color + finalSpec);

    return float4(color.x, color.y, color.z, 1.0);
}