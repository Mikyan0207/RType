#pragma once

#include <memory>
#include <string>
#include <Core.hpp>
#include <filesystem>
#include <RType.Common.hpp>
#include <Exceptions/RTypeException.hpp>

#if defined(_WIN32)
#include <Windows.h>
#include <libloaderapi.h>
#else
#include <dlfcn.h>
#endif

class RTYPECOMMON_API Loader
{
public:
	Loader();
	Loader(const Loader&) = default;
	Loader(Loader&&) noexcept = default;
	~Loader();

public:
	static Shared<Loader> CreateLoader();
	
public:
	Loader& operator=(const Loader&) = default;
	Loader& operator=(Loader&&) noexcept = default;

public:
	void Load(std::string file);
	void Close() const;

	/// <summary>
	/// Instantiate a new class initialized by the entry point passed as parameter.
	/// </summary>
	/// <typeparam name="T">The type of class that will be instantiate.</typeparam>
	/// <param name="entryPoint">Entry point used in the library.</param>
	/// <param name="fromId"></param>
	/// <returns>A new instance of the class T on success.</returns>
	template<class T>
	Shared<T> Instantiate(const std::string& entryPoint)
	{
#if defined(_WIN32)
		auto inst = reinterpret_cast<T * (*)()>(GetProcAddress(m_Library, entryPoint.c_str()));
		if (inst == nullptr)
			throw RTypeException(typeid(Loader).name(), "Loaded library doesn't contain a valid Instantiate function.");

		return Shared<T>(inst());
#else
		auto inst = reinterpret_cast<T * (*)()>(dlsym(m_Library, entryPoint.c_str()));
		if (inst == nullptr)
			throw RTypeException(typeid(Loader).name(), "Loaded library doesn't contain a valid Instantiate function.");

		return Shared<T>(inst());
#endif
	}

private:
#if defined(_WIN32)
	HINSTANCE m_Library;
#else
	void* m_Library;
#endif
};