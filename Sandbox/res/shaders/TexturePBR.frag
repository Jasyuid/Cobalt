#version 330 core

layout(location = 0) out vec4 fragColor;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 texCoord;

uniform sampler2D diffuse;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightCol;