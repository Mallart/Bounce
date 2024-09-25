#pragma once
#include "../include.hpp"
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
		BAPROPERTY(public, protected, ::std::vector<Components::Component*>, Components);
	public:
		virtual ::std::string ToString() { return GetName(); };
		// Returns a pointer on a component if found, 0 otherwise.
		virtual Components::Component* TryGetComponent(::std::string _ComponentName) { for (Components::Component* c : Components) if (c->GetName() == _ComponentName) return c; return 0; }
		// Returns a pointer on a component if found, 0 otherwise.
		virtual Components::Component* TryGetComponent(uint64_t _ComponentID) { for (Components::Component* c : Components) if (c->GetID() == _ComponentID) return c; return 0; }
		// Adds a component by reference.
		virtual void AddComponent(Components::Component & _component) { Components.push_back(&_component); };
		// Adds a component pointer.
		virtual void AddComponent(Components::Component * _component) { Components.push_back(_component); };
		// Returns true if this object is drawable.
		// Objects are not drawable by default.
		virtual bool IsDrawable() { return 0; }
	};

	typedef Object* RefObject;

}