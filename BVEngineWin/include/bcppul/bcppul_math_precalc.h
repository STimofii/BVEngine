//include/bcppul/bcppul_math_precalc.h
#pragma once
#ifndef BCPPUL_MATH_PRECALC_H
#define BCPPUL_MATH_PRECALC_H

#include "bcppul/bcppul_expimp.h"



namespace bcppul {
	class BCPPUL_API Precalculation {
	private:
	protected:
		float step = 0;
		unsigned long long amount = 0;
		float* sinuses = nullptr;
	public:
		Precalculation();
		~Precalculation();
		void precalculateSinuses(unsigned long long amount);
		float getSin(float angle);
		float getCos(float angle);
		float getTan(float angle);
		float getCot(float angle);
	};

	BCPPUL_API float sin(float angle);
	BCPPUL_API float cos(float angle);
	BCPPUL_API float tan(float angle);
	BCPPUL_API float cot(float angle);
	BCPPUL_API Precalculation precalculation;

} // namespace bcppul

#endif