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
	BCLASS(Body) : public Object, public Render::Renderable
	{
		BPROPERTY(protected, Components::RefPhysicsComponent, PhysicsComponent);
		BPROPERTY(protected, Components::RefMeshComponent, MeshComponent);
	public:
		Body() {};
		// Bodies are Renderable by default
		virtual bool IsRenderable() override { return 1; }
		virtual void draw() override
		{

		}
	};
}