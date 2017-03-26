#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "GL\glew.h"
#include <SFML\OpenGL.hpp>
#include <assert.h>
#include <iostream>
#include "InputManager.h"
#include "Mesh.h"
#include "MyShader.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef glm::vec3 Vertex;

int main() {
	sf::ContextSettings settings;
	settings.depthBits = 24; // Request a 24-bit depth buffer
	settings.stencilBits = 8;  // Request a 8 bits stencil buffer
	settings.antialiasingLevel = 0;  // Request 0 levels of antialiasing

	sf::Window window(sf::VideoMode(800, 600), "OpenGL Test", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(100);

	InputManager inputManager;

	glEnable(GL_TEXTURE_2D);
	glewExperimental = GL_TRUE;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	if(glewInit() != GLEW_OK) {
		std::cerr << "Glew failed to initialize" << std::endl;
		return 1;
	}

	glViewport(0, 0, window.getSize().x, window.getSize().y);

	MyShader shader("basicShader.vs", "basicShader.fs");

	window.setActive();	

	sf::Image image;
	if (!image.loadFromFile("smilingcontainer.png")) {
		std::cerr << "Error loading image" << std::endl;
	}
	

	// Texture Options
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);




	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	GLuint indices[] = {
		0, 1, 2,   // First Triangle
		0, 2, 3    // Second Triangle
	};

	Mesh mesh(shader, vertices, 36);

	GLfloat texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};
	mesh.setTexture(image.getPixelsPtr(), image.getSize().x, image.getSize().y, texCoords);

	Mesh mesh2(shader, vertices, 4, indices, 6);
	mesh2.setTexture(image.getPixelsPtr(), image.getSize().x, image.getSize().y, texCoords);


	glm::mat4 model;
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(75.0f), (float)window.getSize().x / window.getSize().y, 0.01f, 100.0f);

	shader.bind();
	GLint modelLoc = glGetUniformLocation(shader.Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	GLint projectionLoc = glGetUniformLocation(shader.Program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));	
	

	Camera camera;

	GLfloat lastX = window.getSize().x / 2;
	GLfloat lastY = window.getSize().y / 2;
	bool firstMouse = true;

	window.setMouseCursorGrabbed(true);
	window.setMouseCursorVisible(false);
	sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);

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

				case sf::Event::MouseMoved: {
					if (firstMouse) // this bool variable is initially set to true (not working right now)
					{
						lastX = sf::Mouse::getPosition(window).x;
						lastY = sf::Mouse::getPosition(window).y;
						firstMouse = false;
					}

					if (sf::Mouse::getPosition(window).x == window.getSize().x / 2 && sf::Mouse::getPosition(window).y == window.getSize().y / 2) {
						break;
					}
					GLfloat xoffset = sf::Mouse::getPosition(window).x - lastX;
					GLfloat yoffset = lastY - sf::Mouse::getPosition(window).y; // Reversed since y-coordinates range from bottom to top				

					camera.ProcessMouseMovement(xoffset, yoffset);
					
					sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
					lastX = sf::Mouse::getPosition(window).x;
					lastY = sf::Mouse::getPosition(window).y;
				} break;
			}
		}

		if (inputManager.isKeyDown(sf::Keyboard::W)) {
			camera.ProcessKeyboard(Camera_Movement::FORWARD, 0.02);
		}
		if (inputManager.isKeyDown(sf::Keyboard::S)) {
			camera.ProcessKeyboard(Camera_Movement::BACKWARD, 0.02);
		}
		if (inputManager.isKeyDown(sf::Keyboard::A)) {
			camera.ProcessKeyboard(Camera_Movement::LEFT, 0.02);
		}
		if (inputManager.isKeyDown(sf::Keyboard::D)) {
			camera.ProcessKeyboard(Camera_Movement::RIGHT, 0.02);
		}


		
		glm::mat4 view;
		view = camera.GetViewMatrix();
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		mesh.setRotation(Rotation(sin(glm::radians(timer.asSeconds())) * 20, 1, 0, 0));

		// clear the buffers
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render
		mesh.render();
		mesh2.render();

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}


	return 0;
}