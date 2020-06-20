#include "LightRender.h"
LightRender::LightRender(MeshType meshType, Camera* camera) // must be implemente to compile
{
	this->camera = camera;
	
	// choose the mesh type
	switch (meshType)
	{
	case kTriangle:
		Mesh::setTriData(vertices, indices); // initialize private varibles
		break;

	case kQuad:
		Mesh::setQuadData(vertices, indices);
		break;
	
	case kCube:
		Mesh::setCubeData(vertices, indices);
		break;

	case kSphere:
		Mesh::setSphereData(vertices, indices);
		break;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER,  sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Enabiling vertex attributes array for attribute reading
	glEnableVertexAttribArray(0);

	// set the gl vertex Attribute pointer as the chain of attributes needs:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::color)));

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}	

LightRender::~LightRender()
{
	// destructor
}

void LightRender::draw()
{
	//printf("light Render draw call \n");
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(glm::mat4(1.0), position);
	glUseProgram(this->program);
	GLint modelLoc = glGetUniformLocation(program, "model");
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 view = camera->getViewMatrix();
	GLint vLoc = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj = camera->getProjectionMatrix();
	GLint pLoc = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(proj));

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	//printf("finising draw \n");
}

void LightRender::setPosition(glm::vec3 _position)
{
	position = _position;
}

void LightRender::setColor(glm::vec3 _color)
{
	color = _color;
}

void LightRender::setProgram(GLuint _program)
{
	program = _program;
}

glm::vec3 LightRender::getPosition()
{
	return position;
}

glm::vec3 LightRender::getColor()
{
	return color;
}
