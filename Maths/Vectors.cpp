#include "Vectors.hpp"

namespace Bounce
{
	namespace Maths
	{

		int64_t Vector2::x() const
		{
			return values[0];
		}

		int64_t Vector2::y() const
		{
			return values[1];
		}

		Vector3::Vector3(int64_t x, int64_t y, int64_t z) : Vector2(x, y)
		{
			values.push_back(z);
		}

		int64_t Vector3::z() const
		{
			return values[2];
		}

		Vector4::Vector4(int64_t x, int64_t y, int64_t z, int64_t w) : Vector3(x, y, z)
		{
			values.push_back(w);
		}

		int64_t Vector4::w() const
		{
			return values[3];
		}

		Vector2d::Vector2d(long double x, long double y) : Vector<long double>{ x, y } {}

		long double Vector2d::x() const
		{
			return values[0];
		}

		long double Vector2d::y() const
		{
			return values[1];
		}

		Vector3d::Vector3d(long double x, long double y, long double z) : Vector2d(x, y)
		{
			values.push_back(z);
		}

		long double Vector3d::z() const
		{
			return values[2];
		}

		Vector4d::Vector4d(long double x, long double y, long double z, long double w) : Vector3d(x, y, z)
		{
			values.push_back(w);
		}

		long double Vector4d::w() const
		{
			return values[3];
		}


		const Vector2 Vector2::Up(0, 1);
		const Vector2 Vector2::Down(0, -1);
		const Vector2 Vector2::Left(-1, 0);
		const Vector2 Vector2::Right(1, 0);
		const Vector3 Vector3::One(0, 0, 0);
		const Vector3 Vector3::Zero(0, 0, 0);
		const Vector3 Vector3::Back(0, 0, -1);
		const Vector3 Vector3::Forward(0, 0, -1);
	}
}