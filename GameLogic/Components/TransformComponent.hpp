#include "Component.hpp"

namespace Bounce
{
	namespace Components
	{
		using namespace Maths;
		// A component that enables 3D transformation, can be used for 2D too.
		BCLASS(TransformComponent) : public Component
		{
		BPROPERTY(protected, Vector3d, Position);
		BPROPERTY(protected, Vector3d, Rotation);
		public:
			TransformComponent(Vector3d _Position, Vector3d _Rotation) : Position{ _Position }, Rotation{ _Rotation } {};

			BGETTER()
				// Returns the component's 3D position 
			Vector3d GetPosition();
			BGETTER()
				// Returns a Vector3 thats is the 
			Vector3d GetRotation();
			BGETTER()
				// Returns the rotation as a Quaternion instead of a Vector3.
			Quaternion GetQuaternion();

			// Moves to the given position
			virtual void MoveTo(Vector3d _Position);
			// Adds the given Vector2 to the current position
			virtual void Move(Vector3d _Position);
			// Rotates to the given rotation (in degrees)
			virtual void RotateTo(Vector3d _Rotation);
			// Adds the given Vector3 to the current rotation (in degrees)
			virtual void Rotate(Vector3d _Rotation);
			// Rotates this object using a quaternion.
			// Prevents Gimbal Lock.
			virtual void Rotate(Quaternion _quat);
			// Returns the relative "up" vector depending on the component's rotation
			virtual Vector3d Up();
			// Returns the relative "right" vector depending on the component's rotation
			virtual Vector3d Forward();
			// Returns the relative "right" vector depending on the component's rotation
			virtual Vector3d Right();

			virtual void Init() override;
			virtual void Update() override;
			virtual void Start() override;
			virtual void End() override;

		};
	}
}