#version 440 core

uniform vec3 lightDirection;
in vec3 normal;

in vec4 pos;
in vec4 col;

out vec4 fragData;

void main()
{
	vec3 LightDirection = normalize(lightDirection);
	vec3 Normal = normalize(normal);
	fragData = col * 1;//clamp(dot(Normal, LightDirection), 0, 1);
}