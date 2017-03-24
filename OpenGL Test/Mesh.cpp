#include "Mesh.h"



Mesh::Mesh(sf::Shader& shader, glm::vec3* vertices, GLuint numVertices, GLuint* indices, GLuint numIndices) :
	_numVertices(numVertices),
	_numIndices(numIndices),
	_shader(&shader)
{
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);
	glGenVertexArrays(1, &_VAO);

	glBindVertexArray(_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), indices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
}

void Mesh::render() {
	sf::Shader::bind(_shader);
	glBindVertexArray(_VAO);
	if (_numIndices) {
		glDrawElements(GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, _numVertices);
	}
	glBindVertexArray(0);
}

void Mesh::setColor(sf::Color color) {
	_shader->setParameter("ourColor", color);
}

void Mesh::setShader(sf::Shader* shader) {
	_shader = shader;
}