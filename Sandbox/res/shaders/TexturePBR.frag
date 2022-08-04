#version 330 core

layout(location = 0) out vec4 fColor;

in VS_OUT {
	vec3 fPos;
	vec2 texCoord;
	mat3 TBN;
	vec3 normal;
} fs_in;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightCol;
uniform float lightInt;

const float PI = 3.14159265359;

vec3 fresnelSchlick(float cosTheata, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheata, 0.0, 1.0), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness*roughness;
	float a2 = a*a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH*NdotH;

	float num = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r*r) / 8.0;

	float num = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);

	return ggx1 * ggx2;
}

void main()
{
	vec3 albedo = texture(albedoMap, fs_in.texCoord).rgb;
	float roughness = texture(roughnessMap, fs_in.texCoord).r;
	float metallic = texture(metallicMap, fs_in.texCoord).r;
	float ao = texture(aoMap, fs_in.texCoord).r;

	vec3 N = texture(normalMap, fs_in.texCoord).rgb;
	N = N * 2.0 - 1.0;
	N = normalize(fs_in.TBN * N);
	//N = normalize(fs_in.normal);
	vec3 V = normalize(viewPos - fs_in.fPos);

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);
	
	vec3 Lo = vec3(0.0);

	vec3 L = normalize(lightPos - fs_in.fPos);
	vec3 H = normalize(V + L);
	float dist = length(lightPos - fs_in.fPos);
	float atten = 1.0 / (dist * dist);
	vec3 radiance = lightCol * lightInt * atten;
	//vec3 radiance = lightCol;


	float NDF = DistributionGGX(N, H, roughness);
	float G = GeometrySmith(N, V, L, roughness);
	vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

	vec3 num = NDF * G * F;
	float denom = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
	vec3 specular = num / denom;

	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - metallic;

	float NdotL = max(dot(N, L), 0.0);
	Lo += (kD * albedo / PI + specular) * radiance * NdotL;

	vec3 ambient = vec3(0.03) * albedo * ao;
	vec3 color = ambient + Lo;

	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0/2.2));

	fColor = vec4(color, 1.0);
}