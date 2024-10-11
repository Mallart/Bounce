#pragma once
#include "../include.hpp"
#include "../IO/Serial.hpp"
#include "../Rendering/Objects/Renderable.hpp"
#include "Components/Component.hpp"

namespace Bounce
{
	// Base object in the engine.
	// Can be derived to create other abstract objects that interact with the World or World's objects.
	BCLASS(Object)
	{
		// This object's name.
		V_BACCESSOR(public, protected, std::string, Name);
		// This object's ID.
		BAPROPERTY(public, protected, uint64_t, ID);
		// Scripts and components attached to this object.
		BAPROPERTY(public, protected, ::std::vector<Components::RefComponent>, Components);
	public:
		virtual ::std::string ToString() { return GetName(); };
		// Returns a pointer on a component if found, 0 otherwise.
		virtual Components::RefComponent TryGetComponent(::std::string _ComponentName) { for (Components::RefComponent c : Components) if (c->GetName() == _ComponentName) return c; return 0; }
		// Returns a pointer on a component if found, 0 otherwise.
		virtual Components::RefComponent TryGetComponent(uint64_t _ComponentID) { for (Components::RefComponent c : Components) if (c->GetID() == _ComponentID) return c; return 0; }
		// Adds a component by reference.
		virtual void AddComponent(Components::Component & _component) { Components.push_back(&_component); };
		// Adds a component pointer.
		virtual void AddComponent(Components::RefComponent _component) { Components.push_back(_component); };
		// Returns true if this object is renderable
		// Objects are not Renderable by default.
		virtual bool IsRenderable() { return dynamic_cast<Render::RefRenderable>(this) ? 1 : 0; }
		// Serializes the object to save it in a file.
		virtual ::std::string Serialize()
		{
			::std::string s;
			return s;
		}

		~Object()
		{
			for (Components::Component* _c : Components)
			{
				_c->End();
				delete _c;
			}
			ID = 0;
		}
	};
}