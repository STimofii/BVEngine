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
	const double DEGREES_IN_RADIAN = 180 / PI;
	const double RADIANS_IN_DEGREE = PI / 180;

	template<typename T>
	inline T map(T a, T aMin, T aMax, T bMin, T bMax) {
		return (a - aMin) * (bMax - bMin) / (aMax - aMin) + bMin;
	}
	template <typename T>
	inline T clamp(T value, T min_val, T max_val) {
		return std::max(min_val, std::min(value, max_val));
	}


	template<typename T>
	inline T distanceFromZero(T x1) {
		return std::sqrt(std::pow(x1, 2));
	}
	template<typename T>
	inline T distanceFromZero(T x1, T y1) {
		return std::sqrt(std::pow(x1, 2) + std::pow(y1, 2));
	}
	template<typename T>
	inline T distanceFromZero(T x1, T y1, T z1) {
		return std::sqrt(std::pow(x1, 2) + std::pow(y1, 2) + std::pow(z1, 2));
	}
	template<typename T>
	inline T distance(T x1, T x2) {
		return std::sqrt(std::pow(x2-x1, 2));
	}
	template<typename T>
	inline T distance(T x1, T x2, T y1, T y2) {
		return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
	}
	template<typename T>
	inline T distance(T x1, T x2, T y1, T y2, T z1, T z2) {
		return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2) + std::pow(z2 - z1, 2));
	}

	template<typename T>
	inline T degreesToRadians(T degrees) {
		return degrees * RADIANS_IN_DEGREE;
	}
	template<typename T>
	inline T radiansToDegree(T radians) {
		return radians * DEGREES_IN_RADIAN;
	}
} // namespace bcppul

#endif