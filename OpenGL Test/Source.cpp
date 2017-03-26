#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "GL\glew.h"
#include <SFML\OpenGL.hpp>
#include <assert.h>
#include <iostream>
#include "InputManager.h"
#include "Mesh.h"
#include "MyShader.h"
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
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(75.0f), (float)window.getSize().x / window.getSize().y, 0.1f, 100.0f);

	shader.bind();
	GLint modelLoc = glGetUniformLocation(shader.Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	GLint projectionLoc = glGetUniformLocation(shader.Program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));	

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	GLfloat cameraSpeed = 0.05f;

	GLfloat yaw = 0;
	GLfloat pitch = 0;

	GLfloat lastX = window.getSize().x / 2;
	GLfloat lastY = window.getSize().y / 2;
	bool firstMouse = true;


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
					if (firstMouse) // this bool variable is initially set to true
					{
						lastX = sf::Mouse::getPosition().x;
						lastY = sf::Mouse::getPosition().y;
						firstMouse = false;
					}

					GLfloat xoffset = sf::Mouse::getPosition().x - lastX;
					GLfloat yoffset = lastY - sf::Mouse::getPosition().y; // Reversed since y-coordinates range from bottom to top
					lastX = sf::Mouse::getPosition().x;
					lastY = sf::Mouse::getPosition().y;

					GLfloat sensitivity = 0.05f;
					xoffset *= sensitivity;
					yoffset *= sensitivity;

					yaw += xoffset;
					pitch += yoffset;

					if (pitch > 89.0f)
						pitch = 89.0f;
					if (pitch < -89.0f)
						pitch = -89.0f;

					cameraFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
					cameraFront.y = sin(glm::radians(pitch));
					cameraFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
					cameraFront = glm::normalize(cameraFront);
				} break;
			}
		}


		if (inputManager.isKeyDown(sf::Keyboard::W)) {
			cameraPos += cameraSpeed * cameraFront;
		}
		if (inputManager.isKeyDown(sf::Keyboard::S)) {
			cameraPos -= cameraSpeed * cameraFront;
		}
		if (inputManager.isKeyDown(sf::Keyboard::A)) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (inputManager.isKeyDown(sf::Keyboard::D)) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}


		
		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

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