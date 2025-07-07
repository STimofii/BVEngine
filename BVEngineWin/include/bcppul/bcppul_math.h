//include/bcppul/bcppul_math.h
#pragma once
#ifndef BCPPUL_MATH_H
#define BCPPUL_MATH_H

#include "bcppul/bcppul_expimp.h"
#include <cmath>


namespace bcppul {
	const double PI = 3.141592653589793;
	const double HALF_PI = 1.570796326794897;
	const double ONE_AND_HALF_PI = PI + HALF_PI;
	const double TAU = 6.2831853071795864;

	template<typename T>
	inline T map(T a, T aMin, T aMax, T bMin, T bMax) {
		return (a - aMin) * (bMax - bMin) / (aMax - aMin) + bMin;
	}
} // namespace bcppul

#endif