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
			Vector(::std::initializer_list<T> _values) : values(_values) {};
			template<typename... Args>
			// Variadic constructor
			Vector(Args... args) : values{ static_cast<T>(args)... } {}
			Vector(const Vector<T>& v) : values{} { values = v.values; };

			BGETTER()
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
			BGETTER()
			Vector<T> Zero()
			{
				Vector<T> _z;
				for (size_t i = 0; i < Size(); ++i)
					_z.Set(i, 0);
				return _z;
			}

			// Returns a vector of the same length filled with 1's.
			BGETTER()
			Vector<T> One()
			{
				Vector<T> _z;
				for (size_t i = 0; i < Size(); ++i)
					_z.Set(i, 1);
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

			operator ::std::string() const 
			{
				if (!Size())
					return ::std::string("Vector0()");
				::std::string ts = "Vector" + ::std::to_string(Size()) + "(" + ::std::to_string(Get(0));
				for (size_t i = 1; i < Size(); ++i)
					ts += "; " + ::std::to_string(Get(i));
				return ts + ")";
			};

			inline virtual ::std::string ToString() override
			{
				return (::std::string)(*this);
			}

			protected:
				::std::string CustomSizeVectorToString(size_t _Size)
				{
					size_t _smaller = min(Size(), _Size);
					if (!_Size)
						return ::std::string("Vector0()");
					::std::string ts = "Vector" + ::std::to_string(_Size) + "(" + ::std::to_string(Get(0));
					size_t i = 1;
					for (; i < _smaller; ++i)
						ts += "; " + ::std::to_string(Get(i));
					return ts + ")";
				}

		};

		// A two-dimensional int vector.
		class Vector2 : public Vector<int64_t>
		{
		public:
			Vector2(int64_t x, int64_t y) : Vector<int64_t>{ x, y } {};
			BGETTER()
				int64_t x();
			BGETTER()
				int64_t y();
			static const Vector2 Up;
			static const Vector2 Down;
			static const Vector2 Right;
			static const Vector2 Left;
			::std::string ToString() { return CustomSizeVectorToString(2); }
		};

		// A three-dimensional int vector.
		class Vector3 : public Vector2
		{
		public:
			Vector3(int64_t x, int64_t y, int64_t z);
			Vector3(Vector2 v) : Vector3{ v.x(), v.y(), 0 } {};
			BGETTER()
				int64_t z();
			static const Vector3 One;
			static const Vector3 Zero;
			static const Vector3 Forward;
			static const Vector3 Back;
			Vector2 GetVector2() { return Vector2(x(), y()); };
			::std::string ToString() { return CustomSizeVectorToString(3); }
		};
		// A four-dimensional int vector.
		class Vector4 : public Vector3
		{
		public:
			Vector4(int64_t x, int64_t y, int64_t z, int64_t w);
			Vector4(Vector2 v) : Vector4(v.x(), v.y(), 0, 0) {};
			Vector4(Vector3 v) : Vector4(v.x(), v.y(), v.z(), 0) {};
			BGETTER();
			int64_t w();
			Vector3 GetVector3() { return Vector3(x(), y(), z()); };
			::std::string ToString() { return CustomSizeVectorToString(4); }
		};

		// A two-dimensional double vector.
		class Vector2d : public Vector<long double>
		{
		public:
			Vector2d(long double x, long double y);
			long double x();
			long double y();
			::std::string ToString() { return CustomSizeVectorToString(2); }

		};

		// A three-dimensional int vector.
		class Vector3d : public Vector2d
		{
		public:
			Vector3d(long double x, long double y, long double z);
			long double z();
			::std::string ToString() { return CustomSizeVectorToString(3); }
		};
		// A four-dimensional int vector.
		class Vector4d : public Vector3d
		{
		public:
			Vector4d(long double x, long double y, long double z, long double w);
			long double w();
			::std::string ToString() { return CustomSizeVectorToString(4); }
		};
	}
}