#version 330 core

layout(location = 0) out vec4 color;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 texCoord;

uniform sampler2D diffuse;

void main()
{
	color = texture(diffuse, texCoord);
};