#pragma once
#include "Object.hpp"

namespace Bounce
{

	// Class to describe the behavior of a scene / World.
	BCLASS(World): public Object
	{
		// World's Uri (path to file)
		BAPROPERTY(public, protected, ::std::string, Uri);
		// World content
		BAPROPERTY(public, protected, ::std::vector<Object*>, Objects);

	protected:
		// A list of objects in this world that are renderable / drawable.
		::std::vector<Render::RefRenderable> RenderableObjects;
	public:
		World() { Uri = ""; };
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
		// Attach an object to this world. Returns true if the operation was successful and if check is enabled.
		bool AttachObject(Object* _object, bool _check = false);
		// Detach an object from this world. Returns true if the operation was successful and if check is enabled.
		bool DetachObject(Object* _object, bool _check = false);
		// Returns only the drawable objects in this Scene / World.
		const ::std::vector<Render::RefRenderable> GetDrawable() const;
	};
}