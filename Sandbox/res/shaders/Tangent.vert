#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;
layout(location = 3) in vec3 vTangent;
layout(location = 4) in vec3 vBitangent;

out VS_OUT {
	vec3 fPos;
	vec2 texCoord;
	mat3 TBN;
	vec3 normal;
} vs_out;

uniform mat4 model;
uniform mat4 camera;

void main()
{
	vs_out.fPos = vec3(model * vec4(vPos, 1.0));
	vs_out.texCoord = vTexCoord;

	vec3 T = normalize(vec3(model * vec4(vTangent, 0.0)));
	vec3 N = normalize(vec3(model * vec4(vNormal, 0.0)));
	//T = normalize(T - dot(T, N) * N);
	//vec3 B = cross(N, T);
	vec3 B = normalize(vec3(model * vec4(vBitangent, 0.0)));

	vs_out.TBN = mat3(T, B, N);
	vs_out.normal = normalize(mat3(model) * vNormal);;
	
	gl_Position = camera * model * vec4(vPos, 1.0);
};