#version 440 core

in vec4 pos;
in vec4 col;

out vec4 fragData;

void main()
{
	fragData = col;
}