#include "Object.hpp"

namespace Bounce
{
	/*
		A class used to describe the behavior of a physical object in the scene.
		Can be static, dynamic, ruled by physics or not, triggered by events or not...
		Basically an object with a Collider component
	*/
	BCLASS() Body : public Object
	{

	};
}