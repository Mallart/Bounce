#include <iostream>
#include "BounceEngine.hpp"
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
				break;
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

using namespace Bounce;

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
	Bounce::Maths::Vector<long double> v12( 5, 7, 8, 9, 5, 8, 3, 5, 7, 8, 3, 4, 5, 7, 8 );
	std::cout << v12.ToString() << std::endl;
	std::cout << Maths::Vector2(1,2).ToString() << std::endl;
	std::cout << Maths::Vector3(1,2,3).ToString() << std::endl;
	std::cout << (::std::string)(Maths::Vector4)Maths::Vector3::Up << std::endl;
	std::cout << (::std::string)Maths::Vector4(5, 4, 3, 2).GetVector2() << std::endl;


	Maths::Vector<int> _vec3;
	::std::cout << _vec3.Set(0, 1).Set(1,2).Set(2,8).ToString() << ::std::endl;
	_vec3.Set(3) = 5;
	::std::cout << _vec3.ToString() << ::std::endl;



#pragma endregion
	std::cout << std::endl;
#pragma region Quaternions

	::std::cout << Maths::Vector3d(5, 7, 8).Invert().ToString() << ::std::endl;
	::std::cout << (::std::string)Maths::Quaternion(Maths::Vector3d(0, 0, 0)) << ::std::endl;
	::std::cout << Maths::Quaternion(Maths::Vector3d(54, 178, 3)).GetNorm() << ::std::endl;
	::std::cout << (::std::string)Maths::Quaternion(Maths::Vector3d(0, 90, 90)).Rotate({ 0, 1, 1 }) << ::std::endl;

	::std::cout << Maths::Vector<int>(5, 6, 78, 8, 8, 7 ,9 ,6 ,63).ToString() << ::std::endl;

#pragma endregion
	std::cout << std::endl;
#pragma region Components
#pragma region Transform
	Components::TransformComponent _tc(Maths::Vector3::Zero, Maths::Vector3::Zero);
	//_tc.Move((Maths::Vector3d)(Maths::Vector3::Up) * 3.0L);
	::std::cout << ::std::string("Transform position: ") << _tc.GetPosition().ToString() << ::std::endl;
#pragma endregion
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
	window.create(sf::VideoMode::getDesktopMode(), "Bounce Physics", sf::Style::Fullscreen);
	window.setFramerateLimit(MAX_FPS);
	Bounce::runWindow(window);
	return 0;
}