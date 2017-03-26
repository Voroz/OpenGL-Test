#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GL\glew.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class MyShader
{
public:
	// Constructor reads and builds the shader
	MyShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~MyShader();

	void bind();
	// Add overloads of these when needed
	void setUniform(const GLchar*, glm::mat4& transform);

	// The program ID
	GLuint Program;

private:
	
};

