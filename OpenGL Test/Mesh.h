#pragma once
#include <glm\glm.hpp>
#include <GL/glew.h>
#include <SFML\Window.hpp>

class Mesh {

public:
	Mesh(glm::vec3* vertices, GLuint numVertices, GLuint* indices = nullptr, GLuint numIndices = 0);
	virtual ~Mesh();
	void render();

private:

	GLuint _VAO;
	GLuint _VBO;
	GLuint _EBO;
	GLuint _numVertices;
	GLuint _numIndices;
};