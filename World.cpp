#include "World.hpp"

namespace Bounce
{
	World::World(::std::string _Uri)
	{ 
		Uri = _Uri;
		if (!IO::LookUpResource(_Uri))
		{
			// Creates a new world.
		}
	}

	World* World::Load(::std::string uri)
	{
		World* _w = new World(uri);

		return _w;
	}

	void World::Unload()
	{
		for (size_t i = 0; i < Objects.size(); ++i)
			delete &Objects[i];
		delete this;
	}

	World* World::Reload()
	{
		// TODO
		return this;
	}

	World* World::Create(::std::string _Uri)
	{
		World* _w = new World(_Uri);
		return _w;
	}

}