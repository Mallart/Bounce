#pragma once
#include "Maths/Maths.hpp"
#include "GameLogic/Game.hpp"
#include "Rendering/Window/BounceWindow.hpp"

// The engine uses features from this version and does not support graphic cards under this.
#define MIN_GL_VERSION_SUPPORTED 3.0

using namespace Bounce;
void InitEngine(const char* _WindowName)
{
	// window declaration (keep only one window)
	sf::RenderWindow window;
	BounceWindow win(_WindowName);
	std::string glVersion = (char*)glGetString(GL_VERSION);
	glVersion = glVersion.substr(0, glVersion.find(" "));
	glewInit();

	if (::std::stoi(glVersion) < MIN_GL_VERSION_SUPPORTED)
	{
		::std::cout << ::std::endl << "Couldn't start engine because of too early version of OpenGL: " << glGetString(GL_VERSION) << ::std::endl;
		::std::cout << "Minimum required version of OpenGL: " << MIN_GL_VERSION_SUPPORTED << ::std::endl;
		exit_throw(Errors::EARLY_GL_VERSION);
	}
	else
	{
		::std::cout << "Starting engine with OpenGL version: " << glGetString(GL_VERSION) << ::std::endl;

	}
	win.Show();
}