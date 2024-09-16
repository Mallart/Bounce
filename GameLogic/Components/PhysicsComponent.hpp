#include "Component.hpp"

namespace Bounce
{
	namespace Components
	{
		// Basic physics component implementing gravity, temperature, elasticity and buoyancy.
		BCLASS() PhysicsComponent : public Component
		{
		public:
			PhysicsComponent()
			{

			};
		}
	}
}