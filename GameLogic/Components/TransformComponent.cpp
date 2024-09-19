#include "TransformComponent.hpp"

namespace Bounce::Components
{
	void TransformComponent::MoveTo(Vector3d _Position)
	{
		Position = _Position;
	}

	void TransformComponent::Move(Vector3d _Position)
	{
		Position += _Position;
	}

	void TransformComponent::RotateTo(float _Rotation)
	{
		Rotation = fmod(_Rotation, 360.f) ;
	}

	void TransformComponent::Rotate(float _Rotation)
	{
		Rotation += fmod(_Rotation, 360.f);
	}

	Vector2d TransformComponent::Up()
	{
		return (Vector2d)Vector2::Up * cos(Rotation);
	}
}
