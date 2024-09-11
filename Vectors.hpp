#include <vector>
#include <cmath>
#include <cstdarg>
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
			Vector(T _values...);

			T Get(size_t index);
			void Set(size_t index, T value);

			// Returns the vector's magnitude.
			long double Magnitude();

			// Returns this vector's distance compared to an other.
			long double Distance(const Vector& _other);

			size_t Size();

			Vector<T> operator+ (const Vector<T>& v1);
			Vector<T> operator- (const Vector<T>& v1);


		};

		// A two-dimensional int vector.
		class Vector2 : Vector<long long>
		{
		protected:
			long long x;
			long long y;
		};

		// A three-dimensional int vector.
		class Vector3 : Vector2
		{
			long long z;
		};
		// A four-dimensional int vector.
		class Vector4 : Vector3
		{
			long long w;
		};

	}
}