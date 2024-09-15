#include "Object.hpp"

namespace Bounce
{
	// A single-instance per World object.
	// For example, a score counter, a Player manager, a weather manager...
	BCLASS() Singleton : public Object
	{

	};
}