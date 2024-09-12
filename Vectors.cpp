#include "Vectors.hpp"

namespace Bounce
{
	namespace Maths
	{

		template<typename T>
		Vector<T> Vector<T>::operator+(const Vector<T>& v1)
		{
			Vector<T> const bigger = v1.Size() > this->Size() ? v1 : *this;
			Vector<T> v(bigger);
			for (size_t i = 0; i < bigger.Size(); ++i)
				v.Set(i, this->Get(i) + v1.Get(i));
			return v;
		}

		template<typename T>
		Vector<T> Vector<T>::operator*(const Vector<T>& v1)
		{
			Vector<T> const bigger = v1.Size() > this->Size() ? v1 : *this;
			Vector<T> v(bigger);
			for (size_t i = 0; i < bigger.Size(); ++i)
				v.Set(i, this->Get(i) * v1.Get(i));
			return v;
		}

		template<typename T>
		Vector<T> Vector<T>::operator/(const Vector<T>& v1)
		{
			Vector<T> const bigger = v1.Size() > this->Size() ? v1 : *this;
			Vector<T> v(bigger);
			for (size_t i = 0; i < bigger.Size(); ++i)
				v.Set(i, static_cast<long double>(this->Get(i) / v1.Get(i)));
			return v;
		}

		template<typename T>
		Vector<T> Vector<T>::operator-(const Vector<T>& v1)
		{
			Vector<T> bigger = v1.Size() > this->Size() ? v1 : *this;
			Vector<T> v(bigger);
			for (size_t i = 0; i < bigger.Size(); ++i)
				v.Set(i, this->Get(i) - v1.Get(i));
			return v;
		}

		template<typename T>
		Vector<T> Vector<T>::operator==(const Vector<T>& v1)
		{
			if (Size() != v1.Size())
				return false;
			for (size_t i = 0; i < Size(); ++i)
				if (Get(i) != v1.Get(i))
					return false;
			return false;
		}

		Vector2::Vector2(long long x, long long y) : Vector<long long>(x, y)
		{
			this->x = x;
			this->y = y;
		}

		Vector3::Vector3(long long x, long long y, long long z) : Vector2(x, y)
		{
			this->z = z;
		}

		Vector4::Vector4(long long x, long long y, long long z, long long w) : Vector3(x, y, z)
		{
			this->w = w;
		}
		Vector2d::Vector2d(long double x, long double y) : Vector<long double>(x, y)
		{
			this->x = x;
			this->y = y;
		}

		Vector3d::Vector3d(long double x, long double y, long double z) : Vector2d(x, y)
		{
			this->z = z;
		}

		Vector4d::Vector4d(long double x, long double y, long double z, long double w) : Vector3d(x, y, z)
		{
			this->w = w;
		}
	}
}