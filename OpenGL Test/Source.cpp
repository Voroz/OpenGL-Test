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
	sf::Window window(sf::VideoMode(800, 600), "OpenGL Test");
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
		0.5f, -0.5f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,   // Bottom Left
		0.0f,  0.5f, 0.0f    // Top 
	};

	GLuint indices[] = {
		0, 2, 5,   // First Triangle
		2, 4, 6    // Second Triangle
	};

	Mesh mesh(shader, vertices, 3);
	mesh.setColor(0.8f, 0.5f, 0.2f, 1.0f);
	mesh.setVertexColor(2, 1.0f, 0.0f, 0.0f);

	bool running = true;
	while (running)
	{
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

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render
		mesh.render();

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}



	return 0;
}