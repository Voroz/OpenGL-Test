#pragma once
#include <glm\glm.hpp>
#include <GL/glew.h>
#include <SFML\Window.hpp>
#include <SFML\Graphics\Shader.hpp>

class Mesh {

public:
	Mesh(sf::Shader& shader, glm::vec3* vertices, GLuint numVertices, GLuint* indices = nullptr, GLuint numIndices = 0);
	virtual ~Mesh();
	void render();
	void setColor(sf::Color color);
	void setShader(sf::Shader* shader);

private:

	GLuint _VAO;
	GLuint _VBO;
	GLuint _EBO;
	GLuint _numVertices;
	GLuint _numIndices;
	sf::Shader* _shader;
};