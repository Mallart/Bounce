#include "./Vectors.hpp"

namespace Bounce::Maths
{
	// Enables precise rotation in 3D.
	BCLASS(Quaternion)
	{
		BPROPERTY(protected, Vector3d, Axis);
		// Scalar part of the quaternion
		BPROPERTY(protected, long double, w);
	public:
		Quaternion(Vector3d v, long double w = 0);
		Quaternion(long double vx, long double vy, long double vz, long double w = 0) : Quaternion(Vector3d(vx, vy, vz), w) {};
		Quaternion(Vector3 v, long double w = 0) : Quaternion(Vector3d(v.x(), v.y(), v.z()), w) {};

		// Copies the quaternion and returns it.
		const Quaternion GetQuaternion() const { return { Axis.Get(0), Axis.Get(1), Axis.Get(2), w}; }
		const Vector3d GetVector3d() const { return { Axis.Get(0), Axis.Get(1), Axis.Get(2) }; }

		Quaternion operator*(const Quaternion& q)
		{
			long double 
				qx = q.Axis.Get(0),
				qy = q.Axis.Get(1),
				qz = q.Axis.Get(2);
			return
			{
				Vector3d(
					w * qx + Axis.x() * q.w + Axis.y() * qz - Axis.z() * qy,
					w * qy - Axis.x() * qz + Axis.y() * q.w + Axis.z() * qx,
					w * qz + Axis.x() * qy - Axis.y() * qx + Axis.z() * q.w
				),
				w* q.w - Axis.x() * qx - Axis.y() * qy - Axis.z() * qz
			};
		}

		// Rotates a Vector3d using this Quaternion
		Vector3d Rotate(Vector3d v)
		{
			return (*this * Quaternion(v.x(), v.y(), v.z(), .0) * Conjugate()).GetVector3d();
		};

		// Rotates a Vector3d using a Quaternion
		inline static Vector3d Rotate(Vector3d v, Quaternion& const q)
		{
			return q.Rotate(v);
		}

		Quaternion Conjugate() const
		{
			return Quaternion(Vector3d(Axis.Invert()), w);
		}
		BGETTER()

	};
}