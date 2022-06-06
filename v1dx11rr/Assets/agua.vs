// el vertex shader del agua no tiene cambio alguno con
// el del terreno, es practicamente igual

#version 400

in vec3 inputPosition;
in vec3 inputNormal;
in vec2 inputTexCoord;
in vec3 inputTangent;
in vec3 inputBinormal;

out vec2 texCoord;
out vec2 texCoordMove;
out vec3 normal;
out vec3 tang;
out vec3 binorm;
out vec3 viewDirection;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec4 viewPosition;

uniform float moveTexture;

void main(void)
{
	// Calculate the position of the vertex against the world, view, and projection matrices.
	gl_Position = worldMatrix * vec4(inputPosition, 1.0f);

	// calculamos direccion de la vista para el specular
	viewDirection = vec3(normalize(viewPosition - gl_Position));

	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;

	// movemos las texturas
	texCoord = inputTexCoord;
	texCoordMove = inputTexCoord;
	texCoordMove.x = texCoordMove.x + moveTexture;
	
	// Calculate the normal vector against the world matrix only.
	normal = vec3(worldMatrix * vec4(inputNormal, 0));
	vec3 tangente = vec3(worldMatrix * vec4(inputTangent,0));
	vec3 binormal = vec3(worldMatrix * vec4(inputBinormal,0));

	// Normalize the normal vector.
	normal = normalize(normal);
	tang = normalize(tangente);
	binorm = normalize(binormal);	
}