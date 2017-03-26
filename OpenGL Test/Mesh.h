#pragma once
#include <glm\glm.hpp>
#include <GL/glew.h>
#include <SFML\Window.hpp>
#include "MyShader.h"

struct Rotation {
	Rotation(float radians, float x, float y, float z) :
		angle(radians),
		x(x),
		y(y),
		z(z) {

	};
	float x;
	float y;
	float z;
	float angle;
};

class Mesh {

public:
	Mesh(MyShader& shader, GLfloat* vertices, GLuint numVertices, GLuint* indices = nullptr, GLuint numIndices = 0);
	virtual ~Mesh();
	void render();
	GLuint verticeCount();
	void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	void Mesh::setVertexColor(GLint index, GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	void setRotation(Rotation rotation);
	void setShader(MyShader* shader);
	void setTexture(const sf::Uint8* pixels, GLuint width, GLuint height, GLfloat* vertices);
	Rotation getRotation();

private:

	GLuint _VAO;
	GLuint _VBO;
	GLuint _EBO;
	GLuint _Texture;
	GLuint _numVertices;
	GLuint _numIndices;
	GLfloat* _vertices;
	MyShader* _shader;
	Rotation _rotation;
};