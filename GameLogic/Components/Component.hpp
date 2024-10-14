#pragma once
#include "../Event.hpp"
#include "../../Maths/Maths.hpp"
namespace Bounce
{
	namespace Components
	{
		/*
		Used to prefix Components IDs.
		For example, a component with its most significant byte as 0x01 is built-in the engine.
		List subject to changes:
		---------------------------------------------------------------------------------
		|	0x0000000000000000	|	Internal	|	User-made libraries and components	|
		---------------------------------------------------------------------------------
		|	0x0100000000000000	|	Built-in	|		Included with the engine.		|
		---------------------------------------------------------------------------------
		|	0x0200000000000000	|	External	|		 Third-party libraries.			|
		---------------------------------------------------------------------------------
		*/

		BENUM() ComponentClass : uint64_t
		{
			INTERNAL,
			BUILTIN = 0x0100000000000000,
			EXTERNAL = 0x0200000000000000,
		};

		// A component that can be attached to any object.
		BINTERFACE(Component)
		{
			// The component's DisplayName.
			BAPROPERTY(public, protected, ::std::string, Name);
			// The component's ID. Used to retrieve a component in an Object.
			BAPROPERTY(public, protected, uint64_t, ID);
		public:
			// Called when the parent object is initiated, before the end of the parent constructor.
			virtual void Init() = 0;
			// Called when the game actually starts
			virtual void Start() = 0;
			// Called before the game shuts down
			virtual void End() = 0;
			// Called every frame from the call of Start() to the call of End()
			virtual void Update() = 0;

			virtual ~Component() = default;
		};
	}
}