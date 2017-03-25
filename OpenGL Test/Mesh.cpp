#include "Mesh.h"



Mesh::Mesh(sf::Shader& shader, GLfloat* vertices, GLuint numVertices, GLuint* indices, GLuint numIndices) :
	_numVertices(numVertices),
	_numIndices(numIndices),
	_shader(&shader)
{

	// Create new vertice array with color and texture space for each vertice included. Set to white as default.
	_vertices = new GLfloat[_numVertices * 9];
	for (GLint i = 0; i < _numVertices; i++) {
		for (GLint j = 0; j < 9; j++) {
			GLint current = i * 9 + j;
			// Position
			if (j < 3) {
				_vertices[current] = vertices[i * 3 + j];
			}
			// Color
			else if (j < 7) {
				_vertices[current] = 1.0f;
			}
			// Texture
			else {
				_vertices[current] = 0.0f;
			}
		}
	}

	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);
	glGenVertexArrays(1, &_VAO);
	glGenTextures(1, &_Texture);

	glBindVertexArray(_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, 9 * _numVertices * sizeof(_vertices[0]), _vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * sizeof(indices[0]), indices, GL_STATIC_DRAW);
		
		// Specify where position is located in the data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
		// Specify where colors are located in the data
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		// Specify where texture points are
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
	delete _vertices;
}

void Mesh::render() {
	sf::Shader::bind(_shader);
	glBindTexture(GL_TEXTURE_2D, _Texture);
	glBindVertexArray(_VAO);	
	if (_numIndices) {
		glDrawElements(GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, _numVertices);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Mesh::verticeCount() {
	return _numVertices;
}

void Mesh::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	assert(r >= 0 && r <= 1 && g >= 0 && g <= 1
		&& b >= 0 && b <= 1 && a >= 0 && a <= 1);

	GLfloat colorData[] = {
		r, g, b, a
	};

	for (GLint i = 0; i < _numVertices * 9; i+=9) {
		_vertices[i + 3] = r;
		_vertices[i + 4] = g;
		_vertices[i + 5] = b;
		_vertices[i + 6] = a;
		glBufferSubData(GL_ARRAY_BUFFER, (i + 3) * sizeof(GLfloat), sizeof(GLfloat) * 4, colorData);
	}
}

void Mesh::setVertexColor(GLint index, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	assert(index < _numVertices
		&& r >= 0 && r <= 1 && g >= 0 && g <= 1
		&& b >= 0 && b <= 1 && a >= 0 && a <= 1);

	GLfloat colorData[] = {
		r, g, b, a
	};

	_vertices[index * 9 + 3] = r;
	_vertices[index * 9 + 4] = g;
	_vertices[index * 9 + 5] = b;
	_vertices[index * 9 + 6] = a;
	glBufferSubData(GL_ARRAY_BUFFER, (index * 9 + 3) * sizeof(GLfloat), sizeof(GLfloat) * 4, colorData);
}

void Mesh::setShader(sf::Shader* shader) {
	_shader = shader;
}

void Mesh::setTexture(const sf::Uint8* pixels, GLuint width, GLuint height, GLfloat* vertices) {
	// Texture	
	glBindTexture(GL_TEXTURE_2D, _Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	for (GLint i = 0; i < _numVertices; i++) {
		for (GLint j = 0; j < 2; j++) {
			GLint current = i * 9 + j + 7;
			_vertices[current] = vertices[i * 2 + j];
		}		
	}
	glBufferData(GL_ARRAY_BUFFER, 9 * _numVertices * sizeof(_vertices[0]), _vertices, GL_STATIC_DRAW);
}