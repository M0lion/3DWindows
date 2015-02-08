#include "Mesh.h"
#include "ShaderUtils.h"
#include <stdio.h>


inline void addPoint(float x, float y, float z, float r, float g, float b, int i, GLfloat *vertices)
{
	vertices[i * 8] = x;
	vertices[i * 8 + 1] = y;
	vertices[i * 8 + 2] = z;
	vertices[i * 8 + 3] = 1;
	vertices[i * 8 + 4] = r;
	vertices[i * 8 + 5] = g;
	vertices[i * 8 + 6] = b;
	vertices[i * 8 + 7] = 1;
}

Mesh::Mesh(int numberOfVertices, int numberOfIndices, GLfloat *vertices, GLushort *indices, GLenum mode, Transform *transform, Shader *shader)
{
	this->numberOfVertices = numberOfVertices;
	this->numberOfIndices = numberOfIndices;

	if (deleteTransform = (!transform))
		transform = new Transform();

	if (deleteShader = (!shader))
		shader = new Shader("basicShader.vsh", "basicShader.fsh");

	this->transform = transform;
	this->shader = shader;

	this->vertices = new GLfloat[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
	{
		this->vertices[i] = vertices[i];
	}

	this->indices = new GLushort[numberOfIndices];
	for (int i = 0; i < numberOfVertices; i++)
	{
		this->indices[i] = indices[i];
	}

	switch (mode)
	{
	case GL_TRIANGLE_STRIP:
		loadToGpu(3);
		break;
	case GL_TRIANGLES:
		loadToGpu(3);
		break;
	case GL_LINE:
		loadToGpu(1);
		break;
	case GL_LINES:
		loadToGpu(1);
		break;
	case GL_LINE_STRIP:
		loadToGpu(1);
		break;
	default:
		loadToGpu(3);
		break;
	}
}

void Mesh::loadToGpu(int verticesPerPrimitive)
{
	//VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numberOfVertices, vertices, GL_STATIC_DRAW);

	//EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * numberOfIndices, indices, GL_STATIC_DRAW);

	//VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GLuint positionHandle = shader->getAttribLocation("position");
	glEnableVertexAttribArray(positionHandle);
	glVertexAttribPointer(positionHandle, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
	if (deleteShader)
		delete(shader);
	if (deleteTransform)
		delete(transform);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

	delete(vertices);
	delete(indices);
}

void Mesh::Draw(Camera *camera)
{
	beginDraw(camera);
	glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_SHORT, 0);
	endDraw();
}

void Mesh::beginDraw(Camera *camera)
{
	shader->Activate();

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	camera->loadToShader();
	//transform->LoadToActiveShader(shader->getUniformLocation("model"));
}

void Mesh::endDraw()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(0);
}