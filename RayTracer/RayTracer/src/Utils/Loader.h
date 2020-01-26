#pragma once

//struct Vertex {
//	glm::vec3 position;
//	glm::vec3 normal;
//
//};

class Triangle;
struct Loader
{
	bool loadOBJ(
		const char * path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec3> & out_normals
	);
};