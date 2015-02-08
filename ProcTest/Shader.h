#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Shader
{
public:
	Shader(GLchar *vertexShader, GLchar *fragmentShader);
	~Shader();

	void Activate();
	static Shader *getCurrentShader();

	GLint getUniformLocation(const GLchar *name);
	GLint getAttribLocation(const GLchar *name);
private:
	static Shader *currentShader;

	GLuint shaderProgram;
	GLuint modelHandle;
	GLuint viewHandle;
	GLuint projectionHandle;
	GLuint lightHandle;
};

