#include "../../include.hpp"
#include "../../Maths/Vectors.hpp"
#include "../../GameLogic/World.hpp"
#include <SFML/OpenGL.hpp>

#define MAX_FPS 144

namespace Bounce
{
	class BounceWindow;
	static void RunWindow(BounceWindow* w);

	BCLASS(BounceWindow) : public ::sf::RenderWindow
	{
		BAPROPERTY(public, protected, World, RenderedWorld)
	public:
		BounceWindow(Maths::Vector2 _resolution, const char* _WindowName = "Bounce Engine")
		{
			create(::sf::VideoMode(_resolution.x(), _resolution.y()), _WindowName, ::sf::Style::Fullscreen);
			setFramerateLimit(MAX_FPS);
			glEnable(GL_DEPTH);
			glEnable(GL_DEPTH_TEST);
			setActive(0);
		}
		BounceWindow(const char* _WindowName = "Bounce Engine") : BounceWindow({::sf::VideoMode::getDesktopMode().width, ::sf::VideoMode::getDesktopMode().height}, _WindowName) {}

		// Makes the window visible in a separate thread.
		void Show()
		{
			::sf::Thread renderThread(&RunWindow, this);
			renderThread.launch();
		}

		void HandleEvents()
		{
			sf::Event event;
			while (pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					close();
					break;
				default:
					break;
				}
			}
		}

		// Adds a world to render.
		void SetScene(const World & _World)
		{
			RenderedWorld = _World;
		}
	};

	static void RunWindow(BounceWindow* w)
	{
		w->setActive(1);

		while (w->isOpen())
		{
			w->HandleEvents();
			w->pushGLStates();
			w->clear(sf::Color::Black);
			w->popGLStates();
			// dessin dans la fenêtre
			w->display();
		}
	}
}