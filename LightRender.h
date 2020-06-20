#pragma once
#include <iostream>
#include <GL/glew.h>
// gl math includes
#include "Dependencies/glm/glm/glm.hpp"
#include "Dependencies/glm/glm/gtc/type_ptr.hpp"

/* include developed clases this can be changed to forwar declaration latter including the structs done
in the mesh class Vertex and MeshType
*/
#include "Mesh.h" // class Mesh;
#include "ShaderLoader.h" // class ShaderLoader;
#include "Camera.h" // class Camera;
// struct Vertex;
// struct MeshType

class LightRender
{
public:
	
	LightRender(MeshType meshType, Camera* camera);
	
	~LightRender();

	void draw();
	void setPosition(glm::vec3 _position);
	void setColor(glm::vec3 _color);
	void setProgram(GLuint _program);

	glm::vec3 getPosition();
	glm::vec3 getColor();

private:
	Camera* camera;
	std::vector<Vertex>vertices; // variable to store vertex array
	std::vector<GLuint>indices;; // variable to store index array
	glm::vec3 position;
	glm::vec3 color;
	GLuint vbo; // vertex buffer object
	GLuint ebo; //element buffer object
	GLuint vao; // vertex array object
	GLuint program;


};

