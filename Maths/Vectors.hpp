#pragma once
#include "Entity.h"
#include <vector>

namespace Bounce
{
	namespace Maths
	{
		// A vector of any type without fixed length.
		// Can theoretically have an infinite number of values.
		BTCLASS(Vector, typename T) : Entity
		{
		protected:
			::std::vector<T> values;
		public:
			Vector(void) : values{} {};
			// Constructor from a list
			Vector(::std::initializer_list<T> _values) : values( _values ) {};
			template<typename... Args>
			// Variadic constructor
			Vector(Args... args) : values{ static_cast<T>(args)... } {}
			Vector(const Vector<T>& v) : values{} { values = v.values; };


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

			// Sets the nth value of this vector to the specified T value.
			// Appends a new value at the end of the Vector if the desired index is equal to the number of elements.
			// Throws an error if the desired index is out of bounds.
			inline Vector<T>& Set(size_t index, T value)
			{
				if (index > Size())
					throw Errors::OUT_OF_BOUNDS;
				else if (index == Size())
					values.push_back(value);
				else
					values[index] = value;
				return *this;
			}

			// Returns a vector of the same length filled with 0's.
			Vector<T> Zero()
			{
				Vector<T> _z;
				for (size_t i = 0; i < Size(); ++i)
					_z.Set(i, 0);
				return _z;
			}

			// Returns the vector's magnitude.
			T Magnitude() const
			{
				T magnitude = 0;
				for (const auto& _val : values)
					magnitude += _val * _val;
				return ::std::sqrt(magnitude);
			}

			// Returns a normalized version of this vector.
			Vector<T> Normalize()
			{
				T magnitude = Magnitude();
				return magnitude > .0f ? *this / magnitude : Zero();
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

			Vector<T> operator+ (const Vector<T>& v1) 
			{
				Vector<T> const bigger = v1.Size() > this->Size() ? v1 : *this;
				Vector<T> v(bigger);
				for (size_t i = 0; i < bigger.Size(); ++i)
					v.Set(i, this->Get(i) + v1.Get(i));
				return v;
			}
			Vector<T> operator* (const Vector<T>& v1)
			{
				Vector<T> const bigger = v1.Size() > this->Size() ? v1 : *this;
				Vector<T> v(bigger);
				for (size_t i = 0; i < bigger.Size(); ++i)
					v.Set(i, this->Get(i) * v1.Get(i));
				return v;
			}
			Vector<T> operator/ (const Vector<T>& v1)
			{
				Vector<T> const bigger = v1.Size() > this->Size() ? v1 : *this;
				Vector<T> v(bigger);
				for (size_t i = 0; i < bigger.Size(); ++i)
					v.Set(i, static_cast<long double>(this->Get(i) / v1.Get(i)));
				return v;
			}
			Vector<T> operator- (const Vector<T>& v1)
			{
				Vector<T> bigger = v1.Size() > this->Size() ? v1 : *this;
				Vector<T> v(bigger);
				for (size_t i = 0; i < bigger.Size(); ++i)
					v.Set(i, this->Get(i) - v1.Get(i));
				return v;
			}
			Vector<T> operator== (const Vector<T>& v1)
			{
				if (Size() != v1.Size())
					return false;
				for (size_t i = 0; i < Size(); ++i)
					if (Get(i) != v1.Get(i))
						return false;
				return false;
			}
			Vector<T>& operator= (const Vector<T>& v1)
			{
				values = v1.values;
				return *this;
			}

			::std::string ToString() override
			{
				if (!Size())
					return ::std::string("Vector0()");
				::std::string ts = "Vector" + ::std::to_string(Size()) + "(" + ::std::to_string(Get(0));
				for (size_t i = 1; i < Size(); ++i)
					ts += "; " + ::std::to_string(Get(i));
				return ts + ")";
			}
		};

		// A two-dimensional int vector.
		class Vector2 : public Vector<long long>
		{
		public:
			Vector2(long long x, long long y);
			long long x();
			long long y();
		};

		// A three-dimensional int vector.
		class Vector3 : public Vector2
		{
		public:
			Vector3(long long x, long long y, long long z);
			long long z();
			static const Vector3 One;
			static const Vector3 Zero;
			static const Vector3 Up;
			static const Vector3 Down;
			static const Vector3 Left;
			static const Vector3 Right;
			static const Vector3 Forward;
			static const Vector3 Back;
		};
		// A four-dimensional int vector.
		class Vector4 : public Vector3
		{
		public:
			Vector4(long long x, long long y, long long z, long long w);
			long long w();
		};

		// A two-dimensional double vector.
		class Vector2d : public Vector<long double>
		{
		public:
			Vector2d(long double x, long double y);
			long double x();
			long double y();
		};

		// A three-dimensional int vector.
		class Vector3d : public Vector2d
		{
		public:
			Vector3d(long double x, long double y, long double z);
			long double z();
		};
		// A four-dimensional int vector.
		class Vector4d : public Vector3d
		{
		public:
			Vector4d(long double x, long double y, long double z, long double w);
			long double w();
		};
	}
}