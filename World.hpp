#include "Object.hpp"


namespace Bounce
{

	// Class to describe the behavior of a scene.
	BCLASS World : Object
	{
	public:

		static World* Load(sf::String uri);
		void Unload();
	};
}