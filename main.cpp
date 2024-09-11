#include "include.hpp"
#include "Game.hpp"
// This project's aim is to display a cool and simple way to implement a physics engine in a graphical
// project using C++ and SFML.

#define MAX_FPS 144

namespace Bounce
{

	void handleEvents(sf::Window& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
			default:
				break;
			}
		}
	}

	void runWindow(sf::RenderWindow& window)
	{
		while (window.isOpen())
		{
			handleEvents(window);
			window.clear(sf::Color::Black);
			// dessin dans la fenêtre
			window.display();
		}
	}


}

void main()
{
	// window declaration (keep only one window)
	sf::RenderWindow window;

	Bounce::Maths::Vector<int>();

	exit(Bounce::Errors::NO_ERROR);

	window.create(sf::VideoMode(1920, 1080), "Bounce Physics", sf::Style::Fullscreen);
	window.setFramerateLimit(MAX_FPS);
	Bounce::runWindow(window);
}