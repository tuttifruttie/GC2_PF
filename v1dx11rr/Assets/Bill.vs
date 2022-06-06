////////////////////////////////////////////////////////////////////////////////
// Filename: Bill.vs
////////////////////////////////////////////////////////////////////////////////
#version 400

// INPUT VARIABLES //
in vec3 inputPosition;
in vec3 inputNormal;
in vec2 inputTexCoord;

// OUTPUT VARIABLES //
out vec2 texCoord;
out vec3 normal;

// UNIFORM VARIABLES //
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
	// Calculate the position of the vertex against the world, view, and projection matrices.
	gl_Position = worldMatrix * vec4(inputPosition, 1.0f);
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;

	// Store the texture coordinates for the pixel shader.
	texCoord = inputTexCoord;

	normal = normalize(vec3(worldMatrix * vec4(inputNormal, 0)));
}