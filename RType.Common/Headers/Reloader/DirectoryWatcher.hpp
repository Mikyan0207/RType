#pragma once

#if defined(_WIN32)
	#include <Windows.h>
#else
	#include <sys/inotify.h>
#endif

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <filesystem>
#include <Core.hpp>
#include <RType.Common.hpp>
#include <Exceptions/RTypeException.hpp>

class RTYPECOMMON_API DirectoryWatcher
{
public:
	explicit DirectoryWatcher(const std::string& path, const std::vector<std::string>& allowedExtensions);
	DirectoryWatcher(const DirectoryWatcher&) = default;
	DirectoryWatcher(DirectoryWatcher&&) noexcept = default;
	~DirectoryWatcher();

public:
	static Shared<DirectoryWatcher> Create(std::string&& path, std::vector<std::string>&& allowedExtensions);
public:
	DirectoryWatcher& operator=(const DirectoryWatcher&) = default;
	DirectoryWatcher& operator=(DirectoryWatcher&&) noexcept = default;

public:
	void Watch(const std::function<void(const std::vector<std::string>&)>& onChange);

private:
	static std::string GetFolderName(const std::string& path);
	std::vector<std::string> FilterFiles();
	
private:
	std::string m_DirectoryPath;
	std::string m_Folder;
	std::vector<std::string> m_AllowedExtensions;

#if defined (_WIN32)
	HANDLE m_DirectoryHandle;
#else
	std::vector<std::string> m_CurrentFiles;
#endif
};
