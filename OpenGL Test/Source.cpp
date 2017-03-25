#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "GL\glew.h"
#include <SFML\OpenGL.hpp>
#include <assert.h>
#include <iostream>
#include "InputManager.h"
#include "Mesh.h"
#include <glm\glm.hpp>

typedef glm::vec3 Vertex;

int main() {
	sf::Window window(sf::VideoMode(700, 700), "OpenGL Test");
	window.setVerticalSyncEnabled(true);
	InputManager inputManager;
	glEnable(GL_TEXTURE_2D);
	glewExperimental = GL_TRUE;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if(glewInit() != GLEW_OK) {
		std::cerr << "Glew failed to initialize" << std::endl;
		return 1;
	}

	glViewport(0, 0, window.getSize().x, window.getSize().y);

	sf::Shader shader;
	if (!shader.loadFromFile("basicShader.vs", "basicShader.fs")) {
		std::cerr << "Shader failed to load" << std::endl;
	}

	window.setActive();

	GLfloat vertices[] = {
		// Positions         // Colors
		0.5f,  0.5f, 0.0f,    // Top Right
		0.5f, -0.5f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,   // Bottom Left		
		-0.5f,  0.5f, 0.0f,    // Top Left
	};

	GLuint indices[] = {
		0, 1, 2,   // First Triangle
		0, 2, 3    // Second Triangle
	};

	sf::Image image;
	if (!image.loadFromFile("main_900.jpg")) {
		std::cerr << "Error loading image" << std::endl;
	}
	image.flipVertically();
	

	// Texture Options
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	Mesh mesh(shader, vertices, 4, indices, 6);	
	mesh.setVertexColor(1, 0.0f, 0.0f, 1.0f);
	mesh.setVertexColor(3, 1.0f, 0.0f, 0.0f);

	GLfloat texCoords[] = {
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};
	mesh.setTexture(image.getPixelsPtr(), image.getSize().x, image.getSize().y, texCoords);

	sf::Clock clock;
	sf::Time timer;	

	bool running = true;
	while (running)
	{
		timer += clock.getElapsedTime();
		clock.restart();
		sf::Event event;

		while (window.pollEvent(event))
		{
			inputManager.update(event);

			switch (event.type) {
				case sf::Event::Closed: {
					running = false;
				} break;

				case sf::Event::MouseButtonPressed: {
					if (event.mouseButton.button == sf::Mouse::Button::Left) {

					}
				} break;

				case sf::Event::MouseButtonReleased: {
					if (event.mouseButton.button == sf::Mouse::Button::Left) {

					}
				} break;
			}
		}

		GLfloat value1 = cos(timer.asSeconds()) / 2 + 0.5;
		GLfloat value2 = sin(timer.asSeconds()) / 2 + 0.5;
		mesh.setVertexColor(3, value1, value2, 0.0f);
		mesh.setVertexColor(0, value2, value2, 0.0f);
		mesh.setVertexColor(1, value2, 0.0f, value1);

		// clear the buffers
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render
		mesh.render();

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}


	return 0;
}