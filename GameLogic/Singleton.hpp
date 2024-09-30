#pragma once
#include "Object.hpp"

namespace Bounce
{
	// A single-instance per World object.
	// For example, a score counter, a Player manager, a weather manager...
	BTCLASS(Singleton, typename T) : public Object
	{
	private:
		static Singleton instance;
	public:
		static Singleton<T> GetInstance() { return instance; }
	};
}