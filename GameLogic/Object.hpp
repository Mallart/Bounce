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
		BPROPERTY(protected, uint64_t, ID);
		BACCESSOR(public, protected, uint64_t, ID);
		// Scripts and components attached to this object.
		BPROPERTY(protected, ::std::vector<Components::Component*>, Components);
		BACCESSOR(public, protected, ::std::vector<Components::Component*>, Components);
	protected:
		virtual void AddComponent(Components::Component & _component) { Components.push_back(&_component); };
	public:
		virtual ::std::string ToString() { return GetName(); };
	};

	typedef Object* RefObject;

}