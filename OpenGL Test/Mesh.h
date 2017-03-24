#pragma once
#include <glm\glm.hpp>
#include <GL/glew.h>
#include <SFML\Window.hpp>
#include <SFML\Graphics\Shader.hpp>

class Mesh {

public:
	Mesh(sf::Shader& shader, GLfloat* vertices, GLuint numVertices, GLuint* indices = nullptr, GLuint numIndices = 0);
	virtual ~Mesh();
	void render();
	GLuint verticeCount();
	void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	void Mesh::setVertexColor(GLint index, GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	void setShader(sf::Shader* shader);

private:

	GLuint _VAO;
	GLuint _VBO;
	GLuint _EBO;
	GLuint _numVertices;
	GLuint _numIndices;
	GLfloat* _vertices;
	sf::Shader* _shader;
};