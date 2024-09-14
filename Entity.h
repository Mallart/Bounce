#pragma once
#include <cmath>
#include <string>
#include "include.hpp"
#include "Errors.hpp"

namespace Bounce
{
	namespace Maths
	{
		// A mathematical entity.
		class Entity
		{
		public:
			virtual ::std::string ToString() = 0;
		};
	}
}