#pragma once
#include "include.hpp"

namespace Bounce
{
	// Base object in the engine.
	// Can be derived to create other abstract objects that interact with the World or World's objects.
	BCLASS Object
	{
		BPROPERTY(public, protected, sf::String, Name);
	};

}