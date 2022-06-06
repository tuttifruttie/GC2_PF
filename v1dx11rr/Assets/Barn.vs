////////////////////////////////////////////////////////////////////////////////
// Filename: Barn.vs
////////////////////////////////////////////////////////////////////////////////
#version 400
// INPUT VARIABLES //
in vec3 inputPosition;
in vec3 inputNormal;
in vec2 inputTexCoord;
in vec3 inputTangent;
in vec3 inputBinormal;

// OUTPUT VARIABLES //
out vec2 texCoord;
out vec3 normal;
out vec3 tangente;
out vec3 binormal;
out vec3 viewDirection;

// UNIFORM VARIABLES //
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 viewPosition;

void main(void)
{
	// calculo de la posicion del vertice
	gl_Position = worldMatrix * vec4(inputPosition, 1.0f);

	// calculamos direccion de la vista para el specular
	viewDirection = vec3(normalize(viewPosition - gl_Position));

	// seguimos con los calculos para posicionar el vertice de acuerdo...
	gl_Position = viewMatrix * gl_Position; // vista de la camara
	gl_Position = projectionMatrix * gl_Position; // tamaño de pantalla

	// coordenadas de textura
	texCoord = inputTexCoord;

	// calculos
	normal = normalize(vec3(worldMatrix * vec4(inputNormal, 0)));
	tangente = normalize(vec3(worldMatrix * vec4(inputTangent, 0)));
	tangente = normalize(tangente - normal * dot(normal, tangente));
	binormal = normalize(cross(normal, tangente));
}