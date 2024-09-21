#pragma once
#include "Entity.hpp"
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

			// Enables the "v.Set(0) = x" syntax.
			inline T& Set(size_t index)
			{
				if (index > Size())
					throw Errors::OUT_OF_BOUNDS;
				else if (index == Size())
				{
					values.push_back(0);
					return values[index];
				}
				else
					return values[index];
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

			// Applies an operation on all members of this vector.
			void Apply(::std::function<T(T)> operation)
			{
				for (size_t i = 0; i < Size(); ++i)
					values[i] = operation(values[i]);
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

			// Sets all the vector's members to their opposite
			Vector<T> Invert() const
			{
				Vector<T> v(*this);
				v.Apply([](T member) -> T { return -member; });
				return v;
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

			Vector<T>& operator+= (const Vector<T>& v1)
			{
				*this = *this + v1;
				return *this;
			}

			Vector<T>& operator-= (const Vector<T>& v1)
			{
				*this = *this - v1;
				return *this;
			}
			Vector<T>& operator*= (const Vector<T>& v1)
			{
				*this = *this * v1;
				return *this;
			}
			Vector<T>& operator/= (const Vector<T>& v1)
			{
				*this = *this / v1;
				return *this;
			}


			inline virtual ::std::string ToString() const override
			{
				if (!Size())
					return ::std::string("Vector0()");
				::std::string ts = "Vector" + ::std::to_string(Size()) + "(" + ::std::to_string(Get(0));
				for (size_t i = 1; i < Size(); ++i)
					ts += "; " + ::std::to_string(Get(i));
				return ts + ")";
			}

			operator ::std::string() const
			{
				return ToString();
			};

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
			int64_t x() const;
			BGETTER()
			int64_t y() const;
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
			int64_t z() const;
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
			int64_t w() const;
			Vector3 GetVector3() { return Vector3(x(), y(), z()); };
			::std::string ToString() { return CustomSizeVectorToString(4); }
		};

		// A two-dimensional double vector.
		class Vector2d : public Vector<long double>
		{
		public:
			Vector2d(long double x, long double y);
			Vector2d(Vector2 v) : Vector2d{ static_cast<long double>(v.x()), static_cast<long double>(v.y()) } {};
			Vector2d(Vector<long double> v) : Vector2d{ v.Get(0), v.Get(1)} {};
			long double x() const;
			long double y() const;
			operator Vector<long double>() { return Vector<long double>(x(), y()); };
			::std::string ToString() { return CustomSizeVectorToString(2); }
		};

		// A three-dimensional double vector.
		class Vector3d : public Vector2d
		{
		public:
			Vector3d(long double x, long double y, long double z);
			Vector3d(Vector3 v) : Vector3d{ static_cast<long double>(v.x()), static_cast<long double>(v.y()), static_cast<long double>(v.z()) } {};
			Vector3d(Vector<long double> v) : Vector3d{ v.Get(0), v.Get(1), v.Get(2)} {};
			long double z() const;
			operator Vector<long double>() { return Vector<long double>(x(), y(), z()); };
			::std::string ToString() { return CustomSizeVectorToString(3); }
		};
		// A four-dimensional double vector.
		class Vector4d : public Vector3d
		{
		public:
			Vector4d(long double x, long double y, long double z, long double w);
			Vector4d(Vector4 v) : Vector4d{ static_cast<long double>(v.x()), static_cast<long double>(v.y()), static_cast<long double>(v.z()), static_cast<long double>(v.w()), } {};
			Vector4d(Vector<long double> v) : Vector4d{ v.Get(0), v.Get(1), v.Get(2), v.Get(3)} {};
			long double w() const;
			operator Vector<long double>() { return Vector<long double>(x(), y(), z(), w()); };
			::std::string ToString() { return CustomSizeVectorToString(4); }
		};
	}
}