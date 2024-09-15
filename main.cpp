#include <iostream>
#include "include.hpp"
#include "Game.hpp"
// This project's aim is to display a cool and simple way to implement a physics engine in a graphical
// project using C++ and SFML.
#define TESTS
#define MAX_FPS 144

namespace Bounce
{

	static void handleEvents(sf::Window& window)
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

	static void runWindow(sf::RenderWindow& window)
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

#ifdef TESTS
static void test()
{
#pragma region Vectors
	Bounce::Maths::Vector<float> _vec;
	_vec = { 4, 5, 6 };
	::std::cout << _vec.ToString() << ::std::endl;
	::std::cout << _vec.Zero().ToString() << ::std::endl;
	Bounce::Maths::Vector<long double> v3{ 5.f, 2.f, 6.f };
	Bounce::Maths::Vector<long double> v3_2{ 3.f, 2.f, 4.f };
	std::cout << v3.Magnitude() << std::endl;
	std::cout << v3.Distance(v3_2) << std::endl;
	Bounce::Maths::Vector<long double> v12{ 5, 7, 8, 9, 5, 8, 3, 5, 7, 8, 3, 4 };
	std::cout << v12.ToString() << std::endl;
#pragma endregion
	std::cout << std::endl;
#pragma region World

#pragma endregion
	exit(Bounce::Errors::NO_ERROR);
}
#endif

int main()
{
	// window declaration (keep only one window)
	sf::RenderWindow window;
#ifdef TESTS
	test();
#endif
	window.create(sf::VideoMode(1920, 1080), "Bounce Physics", sf::Style::Fullscreen);
	window.setFramerateLimit(MAX_FPS);
	Bounce::runWindow(window);
	return 0;
}