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
		BPROPERTY(protected, float, Rotation);
		public:
			TransformComponent(Vector3d _Position, float _Rotation);

			// Moves to the given position
			virtual void MoveTo(Vector3d _Position);
			// Adds the given Vector2 to the current position
			virtual void Move(Vector3d _Position);
			// Rotates to the given rotation (in degrees)
			virtual void RotateTo(float _Rotation);
			// Adds the given Vector2 to the current rotation (in degrees)
			virtual void Rotate(float _Rotation);
			// Returns the relative "up" vector depending on the component's rotation
			virtual Vector2d Up();
			// Returns the relative "right" vector depending on the component's rotation
			virtual Vector2d Right();

			virtual void Init() override;
			virtual void Update() override;
			virtual void Start() override;
			virtual void End() override;

		};
	}
}