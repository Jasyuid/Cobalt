#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTC;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 camera;

void main()
{
	fragPos = vec3(model * vec4(vertexPos, 1.0));
	fragNormal = normalize(mat3(model) * vertexNormal);
	//fragNormal = vertexNormal;
	texCoord = vertexTC;
	
	gl_Position = camera * model * vec4(vertexPos, 1.0);
};