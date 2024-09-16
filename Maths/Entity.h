#pragma once
#include "../include.hpp"
#include <cmath>
#include <string>
#include "../Debug/Errors.hpp"

namespace Bounce
{
	namespace Maths
	{
		// A mathematical entity.
		BCLASS() Entity
		{
		public:
			virtual ::std::string ToString() = 0;
		};
	}
}