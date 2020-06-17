#pragma once
#include <vector>
#include "Dependencies/glm/glm/glm.hpp"

enum MeshType
{
	// coma separated elementes. enums can be created in single line
	kTriangle = 0,
	kQuad = 1,
	kCube = 2,
	kSphere = 3
};

struct Vertex 
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texCoords;
};

class Mesh
{
public:
	
	// Fuction declaration: each function output to references variables a vertex and a indices array
	static void setTriData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	
	static void setQuadData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	static void setCubeData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	static void setSphereData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

};
