#version 440 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

in vec4 position;
in vec4 color;
out vec4 pos;
out vec4 col;

void main()
{
	pos = position;
	col = color;
	//gl_Position = projection * view * model * position;
	gl_Position = projection * view * pos;
}