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
		0.5f,  0.5f, 0.0f,    // Top Right
		0.5f, -0.5f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,   // Bottom Left
		-0.5f,  0.5f, 0.0f    // Top Left
				
	};

	GLuint indices[] = {
		0, 1, 2,   // First Triangle
		0, 2, 3    // Second Triangle
	};

	sf::Image image;
	if (!image.loadFromFile("container.jpg")) {
		std::cerr << "Error loading image" << std::endl;
	}

	// Texture
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.getSize().x, image.getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);


	Mesh mesh(shader, vertices, 4, indices, 6);	
	mesh.setVertexColor(1, 0.0f, 0.0f, 1.0f);
	mesh.setVertexColor(3, 1.0f, 0.0f, 0.0f);

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

		GLfloat greenValue = sin(timer.asSeconds()) / 2 + 0.5;
		mesh.setVertexColor(0, 0.0f, greenValue, 0.0f);

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render
		mesh.render();

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}


	return 0;
}