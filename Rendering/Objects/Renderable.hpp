#include "../../include.hpp"
#include "../../Geometry/Geometry.hpp"

namespace Bounce::Render
{
	BCLASS(Renderable)
	{
	public:
		// Calls OpenGL to draw this object in the defined context.
		virtual void Draw() = 0;
	};
}