#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Camera.h"

#define KEYS 348

#define WINDOWS

class Windows3D
{
public:
	Windows3D();
	~Windows3D();

private:

	int windowWidth = 640;
	int windowHeight = 460;

	void Update();
	void Draw();

	GLFWwindow *window;

	Camera *camera;

	static bool keys[KEYS];//actual type is bool[KEYS]; -- KEYS defined in Windows3D.cpp

	static void keyCallback(GLFWwindow* sender, int key, int scancode, int action, int mods);
};

