#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "InputManager.h"
#include "GL\glew.h"




int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL Test");
	window.setVerticalSyncEnabled(true);
	InputManager inputManager(window);


	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			inputManager.update(event);

			switch (event.type) {
				case sf::Event::Closed: {
					window.close();
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
	}



	return 0;
}