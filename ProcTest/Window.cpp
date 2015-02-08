#include "Window.h"


Window::Window()
{
	transform = new Transform();

	const int numberOfVertices = 4 * 4;
	const int numberOfIndices = 3 * 2;

	GLfloat vertices[numberOfVertices] = 
	{
		-1, -1, 0, 1,
		1, -1, 0, 1,
		-1, 1, 0, 1,
		1, 1, 0, 1
	};

	GLushort indices[numberOfIndices] =
	{
		0, 1, 2,
		1, 2, 3
	};

	mesh = new Mesh(numberOfVertices, numberOfIndices, vertices, indices, GL_TRIANGLE_STRIP, transform, new Shader("windowShader.vsh", "windowShader.fsh"));
}

void Window::Update(float time, bool *keys)
{

}

void Window::Draw(Camera *camera)
{
	mesh->Draw(camera);
}

Window::~Window()
{
	delete(transform);
	delete(mesh);
}
