#pragma once
#include "../include.hpp"
#include <cmath>
#include <string>

namespace Bounce
{
	namespace Maths
	{
		// A mathematical entity.
		BCLASS(Entity)
		{
		public:
			virtual ::std::string ToString() const { return ::std::string("Mathematical Entity"); };
			virtual operator ::std::string() const { return ToString(); };
		};
	}
}
