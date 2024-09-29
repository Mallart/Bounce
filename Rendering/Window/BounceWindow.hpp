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
			sf::ContextSettings settings;
			settings.depthBits = 24;
			settings.stencilBits = 8;
			settings.antialiasingLevel = 4;
			settings.majorVersion = 3;
			settings.minorVersion = 3;

			create(::sf::VideoMode(_resolution.x(), _resolution.y()), _WindowName, ::sf::Style::Fullscreen, settings);
			setActive(1);
			setFramerateLimit(MAX_FPS);
			glEnable(GL_DEPTH_TEST);
			if(glGetError())
				std::cout << "GL error occured while launching window: " << glGetError() <<::std::endl;
		}
		BounceWindow(const char* _WindowName = "Bounce Engine") : BounceWindow({::sf::VideoMode::getDesktopMode().width, ::sf::VideoMode::getDesktopMode().height}, _WindowName) {}

		// Makes the window visible in a separate thread.
		void Show()
		{
			::sf::Thread renderThread(&RunWindow, this);
			// leaves the resourcer free for other threads to access it
			setActive(0);
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
				case sf::Event::Resized:
					glViewport(0, 0, event.size.width, event.size.height);
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
		glClearColor(.95, .15, .15, .1);

		while (w->isOpen())
		{
			w->HandleEvents();
			w->pushGLStates();
			w->clear(sf::Color::Black);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// Draw renderable objects.
			for (Render::RefRenderable _object : w->RenderedWorld.GetDrawable())
				dynamic_cast<Render::RefRenderable>(_object)->draw();
			w->popGLStates();
			// dessin dans la fenêtre
			w->display();
		}
	}
}