//include/bcppul/timer.h
#pragma once
#ifndef TIMER_H
#define TIMER_H

#include "bcppul/bcppul_expimp.h"


#ifdef _MSC_VER
#include <intrin.h>
#endif

#include <iostream>




namespace bcppul {
	BCPPUL_API unsigned long long rdtsc();

	class BCPPUL_API Timer {
	public:
		static const char* pseudo;
		Timer(const char* name = nullptr, bool auto_start = false);
		~Timer();
		Timer(const Timer& other);
		Timer& operator=(const Timer& other);
		Timer(Timer&& other) noexcept;
		Timer& operator=(Timer&& other) noexcept;
		friend bool operator== (const Timer& f, const Timer& s);
		friend bool operator!= (const Timer& f, const Timer& s);
		friend bool operator> (Timer& f, Timer& s);
		friend bool operator< (Timer& f, Timer& s);
		friend bool operator>= (Timer& f, Timer& s);
		friend bool operator<= (Timer& f, Timer& s);
		friend std::ostream& operator<< (std::ostream& out, Timer& timer);

		virtual unsigned long long start();
		virtual unsigned long long stop();
		virtual void printTime();
		virtual void stopAndPrintTime();
		virtual unsigned long long getStart() const;
		virtual unsigned long long getStop() const;
		virtual unsigned long long getTime();
		virtual unsigned long long getRunning() const;
		virtual unsigned long long updateTime();
		virtual long double getTimeSeconds();
		virtual long double getTimeMilliseconds();
		virtual long double getTimeMicroseconds();
		virtual unsigned long long getTimeNanoseconds();
		virtual const char* getName() const;
		virtual void setName(const char* name);

	protected:
		const char* name = nullptr;
		unsigned long long start_time = 0;
		unsigned long long stop_time = 0;
		unsigned long long time = 0;
		bool running = false;

	private:

	};

	class BCPPUL_API SimpleTimer : public Timer{
	public:
		static const char* pseudo;
		SimpleTimer(const char* name = nullptr, bool auto_start = true);
		~SimpleTimer();
	protected:
	private:
	};

	class BCPPUL_API CPUCyclesTimer : public Timer {
	public:
		static const char* pseudo;
		CPUCyclesTimer(const char* name = nullptr, bool auto_start = false);
		~CPUCyclesTimer();
		virtual unsigned long long start() override;
		virtual unsigned long long stop() override;
		virtual unsigned long long updateTime() override;
		virtual unsigned long long getCycles();
		virtual void printTime() override;
		friend BCPPUL_API std::ostream& operator<< (std::ostream& out, CPUCyclesTimer& timer);

	protected:
	private:
		using Timer::getTimeSeconds;
		using Timer::getTimeMilliseconds;
		using Timer::getTimeMicroseconds;
	};
	class BCPPUL_API CPUCyclesSimpleTimer : public CPUCyclesTimer {
	public:
		static const char* pseudo;
		CPUCyclesSimpleTimer(const char* name = nullptr, bool auto_start = true);
		~CPUCyclesSimpleTimer();
	protected:
	private:
	};


} // namespace bcppul

#endif // TIMER_H