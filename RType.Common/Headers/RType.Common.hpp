#pragma once

#if defined(_MSC_VER)
	#ifdef RTYPECOMMON_EXPORTS
		#define RTYPECOMMON_API __declspec(dllexport)
	#elif defined(RTYPECOMMON_INHERITANCE)
		#define RTYPECOMMON_API
	#else
		#define RTYPECOMMON_API __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
	#ifdef RTYPECOMMON_EXPORTS
		#define RTYPECOMMON_API __attribute__((visibility("default")))
	#else
		#define RTYPECOMMON_API
	#endif
#else
	#ifdef RTYPECOMMON_EXPORTS
		#define RTYPECOMMON_API
	#else
		#define RTYPECOMMON_API
	#endif
	#pragma warning Unknown dynamic link semantics.
#endif
