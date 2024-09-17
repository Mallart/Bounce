#pragma once
#include "Object.hpp"

namespace Bounce
{

	// Class to describe the behavior of a scene / World.
	BCLASS() World : Object
	{
		// World's Uri (path to file)
		BPROPERTY(protected, ::std::string, Uri);
		BACCESSOR(public, protected, ::std::string, Uri);
		// World content
		BPROPERTY(protected, ::std::vector<Object*>, Objects);
		BACCESSOR(public, protected, ::std::vector<Object*>, Objects);
	public:
		World(::std::string _Uri);
		// Creates a new world. Same as calling World constructor with a URI pointing to an unavailable ressource.
		static World* Create(::std::string _Uri);
		// Loads a world from its path then returns a new object containing its informations. Same as calling World constructor with a URI pointing to an available ressource.
		static World* Load(::std::string _Uri);
		// Reload the World's Objects to the saved state then return a pointer to the world.
		World* Reload();
		// Destroys all the World content then the world itself in memory.
		// Doesn't affect the World's save.
		void Unload();
	};
}