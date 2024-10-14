#pragma once
#include "../../include.hpp"
#include "../Object.hpp"
// All that the player can interact with.
namespace Bounce::Interactions
{
	// Defines the behavior of a basic player.
	BINTERFACE(Item) : public Object
	{
		// Item's ID (type only, used to compare)
		// This ID should NOT be the instance ID, it's meant to be the Item type ID !
		// May be different from 0.
		BAPROPERTY(public, protected, uint64_t, ID);


	public:
		bool operator==(const Item & other) { return ID == other.ID; };
		bool operator==(const RefItem & other) { return ID == other->ID; };
	};

}