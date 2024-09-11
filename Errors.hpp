#pragma once
// Error handling and list of them.

namespace Bounce
{
	namespace Errors
	{
		enum RuntimeError
		{
			NO_ERROR,
			// occurs when trying to get or set an out of bounds value
			OUT_OF_BOUNDS,
		};
	}
}