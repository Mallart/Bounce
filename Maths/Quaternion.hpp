#include "./Vectors.hpp"
#include "./Radians.hpp"

namespace Bounce::Maths
{
	// Enables precise rotation in 3D.
	BCLASS(Quaternion) : Entity
	{
		BPROPERTY(protected, Vector3d, Axis);
		// Scalar part of the quaternion
		BPROPERTY(protected, long double, w);
	public:
		// Manually sets all the Quaternion's values.
		Quaternion(long double vx, long double vy, long double vz, long double _w = 0) : Axis { vx, vy, vz } { w = _w; }
		// Converts a Vector3d containing Euler angles into a Quaternion using radians.
		Quaternion(Vector3d v, long double w = 0) : Axis{0, 0, 0}, w{0}
		{
			// Converting to radians
			v.Set(0, Radians::DegreesToRadians(v.x()));
			v.Set(1, Radians::DegreesToRadians(v.y()));
			v.Set(2, Radians::DegreesToRadians(v.z()));
			long double
				cosz = cos(v.z() * 0.5),
				sinz = sin(v.z() * 0.5),
				cosy = cos(v.y() * 0.5),
				siny = sin(v.y() * 0.5),
				cosx = cos(v.x() * 0.5),
				sinx = sin(v.x() * 0.5);

			long double
				_w = cosx * cosy * cosz + sinx * siny * sinz,
				x = sinx * cosy * cosz - cosx * siny * sinz,
				y = cosx * siny * cosz + sinx * cosy * sinz,
				z = cosx * cosy * sinz - sinx * siny * cosz;
			Axis.Set(0) = x;
			Axis.Set(1) = y;
			Axis.Set(2) = z;
			this->w = _w;
		}
		// Calls the constructor that uses Vector3d.
		Quaternion(Vector3 v, long double w = 0) : Quaternion(Vector3d(v.x(), v.y(), v.z()), w) {};

		BGETTER()
		// Copies the quaternion and returns it.
		const Quaternion GetQuaternion() const { return { Axis.x(), Axis.y(), Axis.z(), w}; }
		BGETTER()
		const Vector3d GetVector3d() const { return { Axis.x(), Axis.y(), Axis.z() }; }
		BGETTER()
		// Converts a Vector3d that uses Euler angles in degrees to a Quaternion
		static Quaternion GetFromEuler(Vector3d v)
		{
			return Quaternion(v, 0);
		}

		BGETTER()
		// Returns the Quaternion's norm. Should be equal to one, or the quaternion isn't valid.
		const long double GetNorm()
		{
			return ::std::sqrt(Axis.x() * Axis.x() + Axis.y() * Axis.y() + Axis.z() * Axis.z() + w * w);
		}

		Quaternion operator*(const Quaternion& q)
		{
			long double 
				qx = q.Axis.x(),
				qy = q.Axis.y(),
				qz = q.Axis.z();
			return
			{
				w * qx + Axis.x() * q.w + Axis.y() * qz - Axis.z() * qy,
				w * qy - Axis.x() * qz + Axis.y() * q.w + Axis.z() * qx,
				w * qz + Axis.x() * qy - Axis.y() * qx + Axis.z() * q.w,
				w* q.w - Axis.x() * qx - Axis.y() * qy - Axis.z() * qz
			};
		}

		// Rotates a Vector3d using this Quaternion
		Vector3d Rotate(Vector3d v)
		{
			return (*this * Quaternion(v.x(), v.y(), v.z(), .0) * Conjugate()).GetVector3d();
		};

		// Rotates a Vector3d using a Quaternion
		inline static Vector3d Rotate(Vector3d v, Quaternion& q)
		{
			return q.Rotate(v);
		}

		Quaternion Conjugate() const
		{
			Vector3d _inverted(Axis.Invert());
			return Quaternion(_inverted.x(), _inverted.y(), _inverted.z(), w);
		}

		::std::string ToString() const override
		{
			return ::std::string("Quaternion(") + 
				::std::to_string(Axis.x()) + "; " + 
				::std::to_string(Axis.y()) + "; " + 
				::std::to_string(Axis.z()) + "; " + 
				::std::to_string(w) + ")";
		}

		operator ::std::string() const override
		{
			return ToString();
		}
	};
}