#include <vector>
#include <cmath>
#include "Errors.hpp"

namespace Bounce
{
	namespace Maths
	{
		// A vector of any type without fixed length.
		template<typename T>
		class Vector
		{
		protected:
			::std::vector<T> values;
		public:
			template<typename ...Args>
			Vector(Args ..._values) : values{ _values... } {};

			inline size_t Size() const
			{
				return values.size();
			}

			inline T Get(size_t index) const
			{
				if (values.size() < index)
					return 0;
				return values[index];
			}

			inline void Set(size_t index, T value)
			{
				if (index > Size() + 1)
					throw Errors::OUT_OF_BOUNDS;
				else if (index == Size() + 1)
					values.push_back(value);
				else
					values[index] = value;
			}

			// Returns the vector's magnitude.
			T Magnitude() const
			{
				T magnitude = 0;
				for (const auto& _val : values)
					magnitude += _val * _val;
				return ::std::sqrt(magnitude);
			}

			// Returns this vector's distance compared to an other.
			T Distance(const Vector& _other) const
			{
				T _distance = 0;
				for (size_t i = 0; i < Size(); ++i)
				{
					T _temp = Get(i) - _other.Get(i);
					_distance += _temp * _temp;
				}
				return sqrt(_distance);
			}

			Vector<T> operator+ (const Vector<T>& v1);
			Vector<T> operator* (const Vector<T>& v1);
			Vector<T> operator/ (const Vector<T>& v1);
			Vector<T> operator- (const Vector<T>& v1);
			Vector<T> operator== (const Vector<T>& v1);


		};

		// A two-dimensional int vector.
		class Vector2 : public Vector<long long>
		{
		public:
			Vector2(long long x, long long y);
			long long x;
			long long y;
		};

		// A three-dimensional int vector.
		class Vector3 : public Vector2
		{
		public:
			Vector3(long long x, long long y, long long z);
			long long z;
		};
		// A four-dimensional int vector.
		class Vector4 : public Vector3
		{
		public:
			Vector4(long long x, long long y, long long z, long long w);
			long long w;
		};

		// A two-dimensional double vector.
		class Vector2d : public Vector<long double>
		{
		public:
			Vector2d(long double x, long double y);
			long double x;
			long double y;
		};

		// A three-dimensional int vector.
		class Vector3d : public Vector2d
		{
		public:
			Vector3d(long double x, long double y, long double z);
			long double z;
		};
		// A four-dimensional int vector.
		class Vector4d : public Vector3d
		{
		public:
			Vector4d(long double x, long double y, long double z, long double w);
			long double w;
		};

	}
}