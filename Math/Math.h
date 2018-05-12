#pragma once

namespace cpplib
{
	namespace math
	{
		class Math
		{
		public:
			static const float PI;
			static const float Rad2Deg;
			static const float Deg2Rad;

			static bool IsEqual(float a, float b);
			static bool IsEqual(double a, double b);
		};
	} // namespace math
} // namespace cpplib
