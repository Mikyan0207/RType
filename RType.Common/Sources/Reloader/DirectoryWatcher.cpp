#include <Reloader/DirectoryWatcher.hpp>
#include <thread>

/// <summary>
/// Initialize watcher with a directory path.
/// </summary>
/// <param name="path">Path to a directory.</param>
/// <param name="allowedExtensions">Filter files with specific extensions.</param>
DirectoryWatcher::DirectoryWatcher(const std::string& path, const std::vector<std::string>& allowedExtensions)
{
    m_DirectoryPath = path;
	m_AllowedExtensions = allowedExtensions;
#if defined(_WIN32)
    m_DirectoryHandle = nullptr;
#else
#endif
}

/// <summary>
/// Release handle and free resources.
/// </summary>
DirectoryWatcher::~DirectoryWatcher()
{
#if defined(_WIN32)
	if (m_DirectoryHandle != nullptr)
		CloseHandle(m_DirectoryHandle);
#else
#endif
}

/// <summary>
/// Create a Shared<DirectoryWatcher>
/// </summary>
/// <param name="path">Path to a directory.</param>
/// <param name="allowedExtensions">Filter files with specific extensions.</param>
/// <returns>A new instance of DirectoryWatcher.</returns>
Shared<DirectoryWatcher> DirectoryWatcher::Create(std::string&& path, std::vector<std::string>&& allowedExtensions)
{
	return CreateShared<DirectoryWatcher>(std::forward<std::string>(path), std::forward<std::vector<std::string>>(allowedExtensions));
}

/// <summary>
/// Watch modifications on directory and trigger onChange callback if a file is added, modified or renamed.
/// </summary>
/// <param name="onChange">Callback triggered on changes.</param>
void DirectoryWatcher::Watch(const std::function<void(const std::vector<std::string>&)>& onChange)
{
#if defined(_WIN32)
	m_DirectoryHandle = FindFirstChangeNotification(
		m_DirectoryPath.c_str(),
		FALSE,
		FILE_NOTIFY_CHANGE_FILE_NAME
	);

	while (true)
	{
		const auto res = WaitForSingleObject(m_DirectoryHandle, 1000);

		switch (res)
		{
		case WAIT_TIMEOUT:
			break;
		case WAIT_OBJECT_0:
			if (FindNextChangeNotification(m_DirectoryHandle) == false)
				throw RTypeException(typeid(DirectoryWatcher).name(), "FindNextChangeNotification failed.");

			onChange(FilterFiles());

			break;
		default:
			break;
		}
	}
#else
	while (true)
	{
		auto files = std::filesystem::directory_iterator();

		if (!m_DirectoryPath.empty())
		{
			files = std::filesystem::directory_iterator(m_DirectoryPath);
		}

		for (auto&& file : files)
		{
			if (file.is_regular_file())
			{
				const auto it = std::find_if(m_CurrentFiles.begin(), m_CurrentFiles.end(), [&file](const std::string& f)
					{
						return f == file.path().string();
					});

				if (it == m_CurrentFiles.end())
				{
					m_CurrentFiles.emplace_back(*it);
					onChange(FilterFiles());
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
#endif
}

/// <summary>
/// Extract folder name from directory path.
/// </summary>
/// <param name="path">Path of the directory.</param>
/// <returns>Folder name.</returns>
std::string DirectoryWatcher::GetFolderName(const std::string& path)
{
    std::string folder;

    return folder;
}

std::vector<std::string> DirectoryWatcher::FilterFiles()
{
	std::vector<std::string> files;

	for (const auto& e : std::filesystem::directory_iterator(m_DirectoryPath))
	{
		if (!e.is_regular_file())
			continue;

		const auto it = std::find_if(m_AllowedExtensions.begin(), m_AllowedExtensions.end(), [&e](const std::string& ext) -> bool
		{
			const auto str = e.path().string();
			return str.substr(str.find_last_of('.') + 1) == ext;
		});

		if (it == m_AllowedExtensions.end())
			continue;

		files.emplace_back(e.path().string());
	}

	return files;
}
