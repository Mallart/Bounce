#pragma once
#include "include.hpp"
#include "Component.hpp"

namespace Bounce
{
	// Base object in the engine.
	// Can be derived to create other abstract objects that interact with the World or World's objects.
	BCLASS() Object
	{
		// This object's name.
		V_BPROPERTY(public, protected, std::string, Name);
		// This object's ID.
		BPROPERTY(public, protected, __int64, ID);
		// Scripts and components attached to this object.
		BPROPERTY(public, protected, ::std::vector<Component>, Components);
		virtual ::std::string ToString() { return GetName(); };
	};

}