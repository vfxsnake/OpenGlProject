#include "Camera.h"

Camera::Camera(GLfloat FOV, GLfloat width, GLfloat height,
	GLfloat nearPlane, GLfloat farPlane, glm::vec3 camPos)
{
	// asing camPos to cameraPos member variable
	cameraPos = camPos;

	// cusntruct 2 vectors to compose the look at matrix
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f); // 0,0,0 world space to look at
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// asing loat matrix to viewMatrix member variable
	viewMatrix = glm::lookAt(cameraPos, cameraFront, cameraUp);

	// assing the projection matrix membervariable
	projectionMatrix = glm::perspective(FOV, width / height, nearPlane, farPlane);
}

Camera::~Camera()
{
	//destructor
}

glm::mat4 Camera::getViewMatrix()
{
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

glm::vec3 Camera::getCameraPosition()
{
	return cameraPos;
}