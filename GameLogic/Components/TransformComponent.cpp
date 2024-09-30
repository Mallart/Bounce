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

	void TransformComponent::RotateTo(Vector3d _Rotation)
	{
		_Rotation.Apply([](long double x) { return fmod(x, 360.0); });
		Rotation = _Rotation;
	}

	void TransformComponent::Rotate(Vector3d _Rotation)
	{
		_Rotation.Apply([](long double x) { return fmod(x, 360.0); });
		Rotation += _Rotation;
	}

	Vector3d TransformComponent::Up()
	{
		return GetQuaternion().Rotate((Vector3)Vector3::Up);
	}

	Vector3d TransformComponent::Forward()
	{
		return GetQuaternion().Rotate(Vector3::Forward);
	}

	Vector3d TransformComponent::Right()
	{
		return GetQuaternion().Rotate((Vector3)Vector3::Right);
	}

	Vector3d TransformComponent::GetRotation()
	{
		return Rotation;
	}
	Quaternion TransformComponent::GetQuaternion()
	{
		return Quaternion(Rotation);
	}
	Vector3d TransformComponent::GetPosition()
	{
		return Position;
	}
	void TransformComponent::Rotate(Quaternion _quat)
	{
		Rotation = _quat.Rotate(Rotation);
	}

	void TransformComponent::Init()
	{
	}
	void TransformComponent::Update()
	{
	}
	void TransformComponent::Start()
	{
	}
	void TransformComponent::End()
	{
	}

}
