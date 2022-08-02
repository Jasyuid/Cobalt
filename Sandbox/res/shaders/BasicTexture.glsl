#SHADER VERTEX=================================================================
#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNorm;
layout(location = 2) in vec2 vertexTC;

out vec3 fragPos;
out vec3 fragNorm;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 camera;

void main()
{
	gl_Position = camera * model * vec4(vertexPos, 1.0);
	fragPos = vec3(model * vec4(vertexPos, 1.0));
	fragNorm = vertexNorm;
	texCoord = vertexTC;
};

#SHADER FRAGMENT===============================================================
#version 330 core

layout(location = 0) out vec4 color;

in vec3 fragPos;
in vec3 fragNorm;
in vec2 texCoord;

uniform sampler2D diffuse;

void main()
{
	color = texture(diffuse, texCoord);
	//color = vec4(fragNorm, 1.0);
};