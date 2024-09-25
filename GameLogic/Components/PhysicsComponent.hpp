#pragma once
#include "TransformComponent.hpp"

namespace Bounce
{
	namespace Components
	{
		// Basic physics component implementing gravity, temperature, elasticity, and velocity.
		BCLASS(PhysicsComponent) : public TransformComponent
		{
		public:
			// Force applied from the world's gravity to this element.
			BAPROPERTY(public, protected, float, GravityModifier);
			// Object's temperature in Kelvin.
			BAPROPERTY(public, protected, float, Temperature);
			// Elasticity in Pascal.
			BAPROPERTY(public, protected, float, Elasticity);
			// Velocity in m/s.
			BAPROPERTY(public, protected, float, Velocity);


			PhysicsComponent(Vector3d _Pos, Vector3d _Rot, float _Velocity = .0f, float _GravityModifier = .0f, float _Temperature = .0f, float _Elasticity = .0f) : TransformComponent{ _Pos, _Rot }
			{
				GravityModifier = _GravityModifier,
					Temperature = _Temperature,
					Elasticity = _Elasticity;
					Velocity = _Velocity;
			}


		};
	}
}