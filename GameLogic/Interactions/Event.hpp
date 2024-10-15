#pragma once
#include "../../include.hpp"

// Handles events, callbakcs, delegates.
namespace Bounce::Interactions
{
	// A group of methods to be fired when an event occurs
	BCLASS(Event)
	{
		BAPROPERTY(public, private, ::std::vector<BCALLBACK()>, Methods);
	public:
		Event() {};
		Event(::std::initializer_list<BCALLBACK()> methods) { Methods = methods; }

		void AddMethod(BCALLBACK(method))
		{
			Methods.push_back(method);
		}

		void RemoveMethod(BCALLBACK(method))
		{
			for (size_t i = 0; i < Methods.size(); ++i)
				if (Methods[i] == method)
					Methods.erase(Methods.begin() + i, Methods.begin() + i + 1);
		}

		void FireEvent()
		{
			for (void (*_method)() : Methods)
				_method();
		}

		// Returns true if this event will trigger methods when fired
		bool HasMethods()
		{
			return Methods.size();
		}
	};
}