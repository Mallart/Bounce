#include "../../include.hpp"
#include "../../Maths/Vectors.hpp"
#include "../../GameLogic/World.hpp"
#include "../../GameDebug/Console.hpp"
#include "SFML/OpenGL.hpp"
#include "GL/glew.h"

#define MAX_FPS 144

namespace Bounce
{
	class BounceWindow;

	BCLASS(BounceWindow) : public ::sf::RenderWindow
	{
		BAPROPERTY(public, protected, World, RenderedWorld)
		BAPROPERTY(public, protected, Render::UI::RefUIHolder, UIHolder)
		// Color that's drawn where nothing else were.
		BAPROPERTY(public, public, Render::Color, BlankColor);

		BPROPERTY(protected, ::std::thread*, renderThread);
		const Render::Color DEFAULT_BLANK_COLOR{ .95f, .15f, .15f, .1f };
	public:
		BounceWindow(Maths::Vector2 _resolution, const char* _WindowName = "Bounce Engine", Render::Color blankColor = 0) : BlankColor{ blankColor }, renderThread{ 0 }
		{
			sf::ContextSettings settings;
			settings.depthBits = 24;
			settings.stencilBits = 8;
			settings.antialiasingLevel = 4;
			settings.majorVersion = 3;
			settings.minorVersion = 3;

			UIHolder = new Render::UI::UIHolder({new Debug::Console()});

			create(::sf::VideoMode(_resolution.x(), _resolution.y()), _WindowName, ::sf::Style::Fullscreen, settings);
			setActive(1);
			setFramerateLimit(MAX_FPS);
			glEnable(GL_DEPTH_TEST);
			if (glGetError())
				std::cout << "GL error occured while launching window: " << glGetError() << ::std::endl;
		}
		BounceWindow(const char* _WindowName = "Bounce Engine") : BounceWindow({::sf::VideoMode::getDesktopMode().width, ::sf::VideoMode::getDesktopMode().height}, _WindowName) {}

		// Makes the window visible in a separate thread.
		void Show()
		{
			// leaves the resourcer free for other threads to access it
			setActive(0);
			//renderThread = new ::std::thread(&RunWindow, this);
			RunWindow(this);
		}

		void Close()
		{
			::std::cout << "Shutting down engine..." << ::std::endl;
			if(renderThread)

				renderThread->join();

			close();
			::std::cout << "Engine shut down" << ::std::endl;
		}

		void HandleEvents()
		{
			sf::Event event;
			while (pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					Close();
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
		void SetScene(const World& _World)
		{
			RenderedWorld = _World;
		}

		static void RunWindow(RefBounceWindow w)
		{
			w->setActive(1);
			glClearColor(w->BlankColor.nR(), w->BlankColor.nG(), w->BlankColor.nB(), w->BlankColor.nA());

			while (w->isOpen())
			{
				w->HandleEvents();
				w->pushGLStates();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				// Draw renderable objects.
				for (Render::RefRenderable _object : w->RenderedWorld.GetRenderable())
					dynamic_cast<Render::RefRenderable>(_object)->Draw();
				// Draw UI Last
				w->UIHolder->Draw();
				w->popGLStates();
				// dessin dans la fenêtre
				w->display();
			}
			w->setActive(0);
		}

		static void ListenEvents(RefBounceWindow w)
		{
			w->HandleEvents();
		}
	};


}