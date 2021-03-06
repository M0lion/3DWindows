#include "Camera.h"

#define _USE_MATH_DEFINES

#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <math.h>
#include "Shader.h"

Camera::Camera(GLFWwindow *window)
{
	this->window = window;

	xPos = 0;
	yPos = 0;
	zPos = 0;

	xRot = 0;
	yRot = 0;
	zRot = 0;

	UpdateView();
	UpdateProjection();
}

void Camera::loadToShader()
{
	GLint viewHandle = Shader::getCurrentShader()->getUniformLocation("view");
	glUniformMatrix4fv(viewHandle , 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(Shader::getCurrentShader()->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void Camera::UpdateView()
{
	view = glm::mat4();
	glm::mat4 rotation = glm::rotate(glm::mat4(), xRot, glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, yRot, glm::vec3(0, 1, 0));
	
	glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3(xPos, yPos, zPos));

	view = view.operator*=(rotation.operator*=(translate));
}

void Camera::UpdateProjection()
{
	int viewPortWidth = 0, viewPortHeight = 0;
	glfwGetFramebufferSize(window, &viewPortWidth, &viewPortHeight);
	float aspect = (float)viewPortWidth / viewPortHeight;
	projection = glm::perspectiveFov(65.0f, aspect, 1.0f, 0.01f, 100.0f);
}

void Camera::Update(bool keys[])
{

	float xMove = 0, yMove = 0, zMove = 0;

	float moveSpeed = 0.05;
	float turnSpeed = 1.5;

	if (keys[GLFW_KEY_W])
	{
		zMove += moveSpeed;
	}
	if (keys[GLFW_KEY_S])
	{
		zMove -= moveSpeed;
	}
	if (keys[GLFW_KEY_A])
	{
		xMove += moveSpeed;
	}
	if (keys[GLFW_KEY_D])
	{
		xMove -= moveSpeed;
	}
	if (keys[GLFW_KEY_E])
	{
		yMove += moveSpeed;
	}
	if (keys[GLFW_KEY_Q])
	{
		yMove -= moveSpeed;
	}
	if (keys[GLFW_KEY_RIGHT])
	{
		yRot += turnSpeed;
	}
	if (keys[GLFW_KEY_LEFT])
	{
		yRot -= turnSpeed;
	}
	if (keys[GLFW_KEY_DOWN])
	{
		xRot += turnSpeed;
	}
	if (keys[GLFW_KEY_UP])
	{
		xRot -= turnSpeed;
	}

	Move(zMove, xMove, yMove);

	UpdateProjection();
}

void Camera::Move(float forward, float side, float up)
{
	yPos += up;

	float rot = (yRot / 180) * (M_PI);

	xPos += (side * cos(rot)) - (forward * sin(rot));
	zPos += (side * sin(rot)) + (forward * cos(rot));

	UpdateView();
}

Camera::~Camera()
{
}
