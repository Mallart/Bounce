#include "./Vectors.hpp"

namespace Bounce::Maths
{
	// Enables precise rotation in 3D.
	BCLASS(Quaternion)
	{
		BPROPERTY(protected, Vector3d, Axis);
		// Scalar part of the quaternion
		BPROPERTY(protected, double, w);
	public:
		Quaternion(Vector3d v, double w);
		Quaternion(Vector3 v, double w) : Quaternion(Vector3d(v.x(), v.y(), v.z()), w) {};

		Vector3d Rotate(Vector3d v) const
		{

		};

		Quaternion Conjugate() const
		{
			return Quaternion(Vector3d(Axis.Invert()), w);
		}
		BGETTER()

	};
}