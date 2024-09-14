#include "Vectors.hpp"

namespace Bounce
{
	namespace Maths
	{
		Vector2::Vector2(long long x, long long y) : Vector<long long>{ x, y }
		{
			values.push_back(x);
			values.push_back(y);
		}

		long long Vector2::x()
		{
			return values[0];
		}

		long long Vector2::y()
		{
			return values[1];
		}

		Vector3::Vector3(long long x, long long y, long long z) : Vector2(x, y)
		{
			values.push_back(z);
		}

		long long Vector3::z()
		{
			return values[2];
		}

		Vector4::Vector4(long long x, long long y, long long z, long long w) : Vector3(x, y, z)
		{
			values.push_back(w);
		}

		long long Vector4::w()
		{
			return values[3];
		}

		Vector2d::Vector2d(long double x, long double y) : Vector<long double>{ x, y }
		{
			values.push_back(x);
			values.push_back(y);
		}

		long double Vector2d::x()
		{
			return values[0];
		}

		long double Vector2d::y()
		{
			return values[1];
		}

		Vector3d::Vector3d(long double x, long double y, long double z) : Vector2d(x, y)
		{
			values.push_back(z);
		}

		long double Vector3d::z()
		{
			return values[2];
		}

		Vector4d::Vector4d(long double x, long double y, long double z, long double w) : Vector3d(x, y, z)
		{
			values.push_back(w);
		}

		long double Vector4d::w()
		{
			return values[3];
		}


		const Vector3 Vector3::One(0, 0, 0);
		const Vector3 Vector3::Zero(0, 0, 0);
		const Vector3 Vector3::Up(0, 1, 0);
		const Vector3 Vector3::Down(0, -1, 0);
		const Vector3 Vector3::Left(-1, 0, 0);
		const Vector3 Vector3::Right(1, 0, 0);
		const Vector3 Vector3::Back(0, 0, -1);
		const Vector3 Vector3::Forward(0, 0, -1);
	}
}