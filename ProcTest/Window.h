#pragma once

#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"

class Window
{
public:
	Window();
	~Window();

	void Update(float time, bool *keys);
	void Draw(Camera *camera);

private:
	Transform *transform;
	Mesh *mesh;
};

