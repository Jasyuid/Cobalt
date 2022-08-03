#version 330 core

layout(location = 0) out vec4 color;

in vec3 fragPos;
in vec3 fragNormal;

void main()
{
	color = vec4(fragNormal, 1.0);
};