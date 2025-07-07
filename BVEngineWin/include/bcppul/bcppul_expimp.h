//include/bcppul/bcppul_expimp.h
#pragma once
#ifndef BCPPUL_EXPIMP_H
#define BCPPUL_EXPIMP_H

#ifdef _WIN32
	#ifdef BCPPUL_EXPORTS
			#define BCPPUL_API __declspec(dllexport)
		#elif defined(BCPPUL_SHARED_USE)
			#define BCPPUL_API __declspec(dllimport)
		#else
			#define BCPPUL_API
	#endif
#else
	#define BCPPUL_API
#endif

#endif // BCPPUL_EXPIMP_H