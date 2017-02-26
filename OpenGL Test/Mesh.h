#pragma once
#include <glm\glm.hpp>
#include <GL/glew.h>
#include <SFML\Window.hpp>

typedef glm::vec3 Vertex;

class Mesh {

public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	virtual ~Mesh();
	void render();

private:

	enum {
		POSITION_VB,

		NUM_BUFFERS
	};

	GLuint _vertexArrayObject;
	GLuint _vertexArrayBuffers[NUM_BUFFERS];
	unsigned int _drawCount;
};