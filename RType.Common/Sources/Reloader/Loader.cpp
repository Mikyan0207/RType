#include <Reloader/Loader.hpp>

/// <summary>
/// Initialize Loader.
/// </summary>
Loader::Loader()
{
#if defined(_WIN32)
	m_Library = nullptr;
#else
	m_Library = nullptr;
#endif
}

/// <summary>
/// Free loaded Library.
/// </summary>
Loader::~Loader()
{
#if defined(_WIN32)
	if (m_Library != nullptr)
		FreeLibrary(m_Library);
#else
	if (m_Library != nullptr)
		dlclose(m_Library);
#endif
}

/// <summary>
/// Create a new loader.
/// </summary>
/// <returns>A <see cref="Shared{Loader}"/></returns>
Shared<Loader> Loader::CreateLoader()
{
	return CreateShared<Loader>();
}

/// <summary>
/// Load a dynamic library.
/// </summary>
/// <param name="file">Path to file.</param>
void Loader::Load(std::string file)
{
#if defined(_WIN32)
	file = file + ".dll";
	m_Library = LoadLibraryA(file.c_str());

	if (m_Library == nullptr)
		throw RTypeException(typeid(Loader).name(), "Failed to load dynamic Library '" + file + "'.");
#else
	file = "lib" + file + ".so";
	m_Library = dlopen(file.c_str(), RTLD_LAZY);

	if (m_Library == nullptr)
		throw RTypeException(typeid(Loader).name(), "Failed to load dynamic Library '" + file + "'. Error: " + std::string(dlerror()));
#endif
}

void Loader::Close() const
{
#if defined(_WIN32)
	if (m_Library != nullptr)
		FreeLibrary(m_Library);
#else
	if (m_Library != nullptr)
		dlclose(m_Library);
#endif
}
