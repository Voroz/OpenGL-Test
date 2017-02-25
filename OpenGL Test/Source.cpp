#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "GL\glew.h"
#include <SFML\OpenGL.hpp>
#include <assert.h>
#include <iostream>
#include "InputManager.h"



int main() {
	sf::Window window(sf::VideoMode(800, 600), "OpenGL Test");
	window.setVerticalSyncEnabled(true);
	InputManager inputManager(window);
	glEnable(GL_TEXTURE_2D);
	GLenum status = glewInit();
	if(status != GLEW_OK) {
		std::cerr << "Glew failed to initialize" << std::endl;
		return 1;
	}


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

		// draw...

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}



	return 0;
}