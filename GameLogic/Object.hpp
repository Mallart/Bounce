#pragma once
#include "../include.hpp"
#include "Components/Component.hpp"

namespace Bounce
{
	// Base object in the engine.
	// Can be derived to create other abstract objects that interact with the World or World's objects.
	BCLASS() Object
	{
		// This object's name.
		V_BPROPERTY(public, protected, std::string, Name);
		// This object's ID.
		BPROPERTY(public, protected, uint64_t, ID);
		// Scripts and components attached to this object.
		BPROPERTY(public, protected, ::std::vector<Components::Component*>, Components);
	protected:
		virtual void AddComponent(Components::Component & _component) { Components.push_back(&_component); };
	public:
		virtual ::std::string ToString() { return GetName(); };
	};

}