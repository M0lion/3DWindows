#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Camera.h"
#include "Shader.h"
#include "Transform.h"

class Mesh
{
public:
	Mesh(int numberOfVertices, int numberOfIndices, GLfloat *vertices, GLushort *indices, GLenum mode, Transform *transform, Shader *shader);
	~Mesh();

	virtual void Draw(Camera *camera);
protected:
	void loadToGpu(int verticesPerPrimitive);

	void beginDraw(Camera *camera);
	void endDraw();

	GLfloat *vertices;
	GLushort *indices;

	int numberOfVertices;
	static const int sizeOfVertex = 4;
	int numberOfIndices;
private:
	GLuint VBO; //for storing vertices in gpu
	GLuint EBO; //for storing indices in gpu
	GLuint VAO;

	Transform *transform;

	Shader *shader;

	bool deleteShader = false;
	bool deleteTransform = false;
};