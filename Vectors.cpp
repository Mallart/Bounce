#include "Vectors.hpp"

namespace Bounce
{
	namespace Maths
	{
		template<typename T>
		inline T Vector<T>::Get(size_t index)
		{
			if (values.size() < index)
				return 0;
			return values[index];
		}

		template<typename T>
		void Vector<T>::Set(size_t index, T value)
		{
			if (index > Size() + 1)
				throw Errors::OUT_OF_BOUNDS;
			else if (index == Size() + 1)
				values.push_back(value);
			else
				values[index] = value;
		}

		template<typename T>
		long double Vector<T>::Magnitude()
		{
			long double magnitude = .0f;
			for (size_t i = 0; i < Size(); ++i)
			{
				long double _temp = dynamic_cast<long double>(Get(i));
				magnitude += _temp * _temp;
			}
			return sqrt(magnitude);
		}

		template<typename T>
		long double Vector<T>::Distance(const Vector& _other)
		{
			long double _distance = .0f;
			for (size_t i = 0; i < Size(); ++i)
				_distance += abs(Get(i) - _other.Get(i));
			return sqrt(_distance);
		}

		template<typename T>
		inline size_t Vector<T>::Size()
		{
			return values.size();
		}

		template<typename T>
		Vector<T> Vector<T>::operator+(const Vector<T>& v1)
		{
			Vector<T> bigger = v1.Size() > this->Size() ? v1 : *this;
			Vector<T> v(bigger);
			for (size_t i = 0; i < bigger.Size(); ++i)
				v.Set(i, this->Get(i) + v1.Get(i));
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
		inline Vector<T>::Vector(T _values...)
		{
			va_list args;
			va_start(args, _values);
			values = ::std::vector<T>();
			while(*_values)
				values.push_back(va_arg(args, T));
		}
	}
}