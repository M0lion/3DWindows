#include "Windows3D.h"

#include <stdio.h>

#include "Mesh.h"
#include "Window.h"

bool Windows3D::keys[] = {false};

Window *_window;

Windows3D::Windows3D()
{
	if (!glfwInit())
	{
		throw "Could not initialize glfw";
	}

	window = glfwCreateWindow(windowWidth, windowHeight, "ProcTest", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		throw "Could not create window";
	}

	glfwSetKeyCallback(window, keyCallback);

	glfwMakeContextCurrent(window);
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));

	//glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_MAX);

	glClearColor(0, 0, 0, 1);

	camera = new Camera(window);

	_window = new Window();

	while (!glfwWindowShouldClose(window))
	{
		Update();
		Draw();

		GLenum error;
		while ((error = glGetError()) != GL_NO_ERROR)
			fprintf(stderr, "OpenGL error: %s\n", gluErrorString(error));

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Windows3D::Update()
{
	camera->Update((bool*)keys);
	_window->Update(0, (bool*)keys);
}

void Windows3D::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_window->Draw(camera);

	glfwSwapBuffers(window);
}

Windows3D::~Windows3D()
{
}

void Windows3D::keyCallback(GLFWwindow* sender, int key, int scancode, int action, int mods)
{
	keys[key] = action != GLFW_RELEASE;
}
