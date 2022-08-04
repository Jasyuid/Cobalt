#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 camera;

void main()
{
	fragPos = vec3(model * vec4(vPos, 1.0));
	fragNormal = normalize(mat3(model) * vNormal);
	texCoord = vTexCoord;
	
	gl_Position = camera * model * vec4(vPos, 1.0);
};