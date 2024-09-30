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
			delete Objects[i];
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

	const ::std::vector<Render::RefRenderable> World::GetRenderable() const
	{
		return RenderableObjects;
	}
	
	bool World::AttachObject(Object* _object, bool _check)
	{
		bool isRenderable = dynamic_cast<Render::RefRenderable>(_object);
		Objects.push_back(_object);
		// if object is renderable, add it to the list of renderable objects of this world.
		if (isRenderable)
			RenderableObjects.push_back(reinterpret_cast<Render::RefRenderable>(_object));
		if (_check)
		{
			// check
			// checks if it has been added to the list of the World's objects
			bool _c =  ::std::find(Objects.begin(), Objects.end(), _object) != Objects.end();
			// checks if it has been added to the list of the World's renderable objects if it is
			if(isRenderable)
				return _c && ::std::find(RenderableObjects.begin(), RenderableObjects.end(), reinterpret_cast<Render::RefRenderable>(_object)) != RenderableObjects.end();
			return _c;
		}
		return true;
	}
	
	bool World::DetachObject(Object* _object, bool _check)
	{
		bool isRenderable = dynamic_cast<Render::RefRenderable>(_object);
		
		// Removes element from the World's objects list.
		auto _it = ::std::find(Objects.begin(), Objects.end(), _object);
		if (_it != Objects.end())
			Objects.erase(_it);

		// Removes element from the World's renderable objects list, if it is.
		if (isRenderable)
		{
			auto _it = ::std::find(RenderableObjects.begin(), RenderableObjects.end(), reinterpret_cast<Render::RefRenderable>(_object));
			if (_it != RenderableObjects.end())
				RenderableObjects.erase(_it);
		}

		if (_check)
		{
			// check. is true when object is not found anymore in the list.
			bool _c = ::std::find(Objects.begin(), Objects.end(), _object) == Objects.end();
			if (isRenderable)
				return _c && ::std::find(RenderableObjects.begin(), RenderableObjects.end(), reinterpret_cast<Render::RefRenderable>(_object)) == RenderableObjects.end();
			return _c;
		}
		return true;
	}
}

