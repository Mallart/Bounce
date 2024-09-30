#include "../include.hpp"
#define PI 3.14159265358979323846264338327950288419716939937510582L
namespace Bounce::Maths
{
	namespace Radians
	{
		inline static long double DegreesToRadians(long double _degrees)
		{
			return _degrees * PI / 180.0;
		}

		inline static long double RadiansToDegrees(long double _radians)
		{
			return _radians * 180.0 / PI;
		}
	}
}