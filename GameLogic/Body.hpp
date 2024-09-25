#pragma once
#include "Object.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/MeshComponent.hpp"

namespace Bounce
{
	/*
		A class used to describe the behavior of a physical object in the scene.
		Can be static, dynamic, ruled by physics or not, triggered by events or not...
		Basically an object with a Collider component.
	*/
	BCLASS(Body) : public Object, public ::sf::Drawable
	{
		BPROPERTY(protected, Components::PhysicsComponent, PhysicsComponent);
		BPROPERTY(protected, Components::MeshComponent, MeshComponent);
	public:
		// Bodies are drawable by default
		virtual bool IsDrawable() override { return 1; }
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{

		}
	};
}