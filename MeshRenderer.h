#pragma once
#include <vector>
#include "Camera.h"
#include "LightRender.h"

#include <GL/glew.h>

#include "Dependencies/glm/glm/glm.hpp"
#include "Dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/glm/gtc/type_ptr.hpp"

// bullet include:
#include <btBulletDynamicsCommon.h> // this include could be loaded in cpp later and add forward delcaration.

class MeshRenderer
{
public:
	MeshRenderer(MeshType modelType, Camera* _camera, btRigidBody* _rigidBody);
	~MeshRenderer();

	void draw();

	void setPosition(glm::vec3 _position);
	void setScale(glm::vec3 _scale);
	void setProgram(GLuint _program);
	void setTexture(GLint _textureID);

private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	glm::mat4 modelMatrix;
	
	// bullet pointer:
	btRigidBody* rigidBody;

	Camera* camera;
	glm::vec3 position;
	glm::vec3 scale;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint texture;
	GLuint program;
};

