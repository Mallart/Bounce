#pragma once
#include "include.hpp"

namespace Bounce
{
	// Base object in the engine.
	// Can be derived to create other abstract objects that interact with the World or World's objects.
	BCLASS() Object
	{
		V_BPROPERTY(public, protected, std::string, Name);
		virtual ::std::string ToString() { return GetName(); };
	};

}