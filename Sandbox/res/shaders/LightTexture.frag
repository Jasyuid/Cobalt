#version 330 core

layout(location = 0) out vec4 fragColor;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 texCoord;

uniform sampler2D diffuse;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightCol;

void main()
{
	vec3 color = texture(diffuse, texCoord).rgb;

	vec3 ambient = vec3(0.05);

	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 normal = fragNormal;
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * lightCol;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
	vec3 specular = spec * lightCol;

	color *= (ambient + diffuse + specular);
	//color = pow(color, vec3(1.0/2.2));

	fragColor = vec4(color, 1.0);
};