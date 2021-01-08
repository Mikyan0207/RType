#pragma once

#if defined(_MSC_VER)
	#ifdef RTYPEENTITIES_EXPORTS
		#define RTYPEENTITIES_API __declspec(dllexport)
	#else
		#define RTYPEENTITIES_API __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
	#ifdef RTYPEENTITIES_EXPORTS
		#define RTYPEENTITIES_API
	#else
		#define RTYPEENTITIES_API
	#endif
#else
	#ifdef RTYPEENTITIES_EXPORTS
		#define RTYPEENTITIES_API
	#else
		#define RTYPEENTITIES_API
	#endif
	#pragma warning Unknown dynamic link semantics.
#endif