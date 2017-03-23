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

	glm::vec3 vertices[] = {
		glm::vec3(0.5f,  0.5f, 0.0f),  // Top Right
		glm::vec3(0.5f, -0.5f, 0.0f),  // Bottom Right
		glm::vec3(-0.5f, -0.5f, 0.0f),  // Bottom Left
		glm::vec3(-0.5f,  0.5f, 0.0f)   // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};

	Mesh mesh(vertices, 4, indices, 6);

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

		sf::Shader::bind(&shader);
		mesh.render();

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}



	return 0;
}