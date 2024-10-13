#pragma once
// Error handling and list of them.

#define exit_throw(error) ::std::cout << "A fatal error occured and led the program to a crash. Error code: " << error << ::std::endl << "Error name: " << #error << ::std::endl; exit(error)

namespace Bounce
{
	namespace Errors
	{
		enum RuntimeError
		{
			NERROR,
			// Occurs when trying to get or set an out of bounds value
			OUT_OF_BOUNDS,
			// Occurs when trying to start the engine with a gpu using a too early version of OpenGL
			EARLY_GL_VERSION,
			// Occurs when OpenGL meets an error while rendering
			GL_ERROR,
		};
	}
}