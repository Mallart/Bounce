#include "../../include.hpp"

namespace Bounce::Render
{
	BCLASS(Renderable)
	{
	public:
		// Calls OpenGL to draw this object in the defined context.
		virtual void draw() = 0;
	};
}