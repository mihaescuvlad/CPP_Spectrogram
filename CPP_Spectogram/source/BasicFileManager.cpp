#include "BasicFileManager.hpp"

#include <ranges>

BasicFileManager::BasicFileManager(const std::filesystem::path& fileDirectory)
{
	initialize(fileDirectory);
	updateFiles();
}

BasicFileManager::BasicFileManager(std::filesystem::path&& fileDirectory)
{
	initialize(std::move(fileDirectory));
	updateFiles();
}

void BasicFileManager::updateFiles() 
{
	if(std::filesystem::is_directory(m_fileDirectory) == false)
	{
		return;
	}

	m_filePaths.clear();

	for (const auto& file : std::filesystem::directory_iterator(m_fileDirectory)) 
	{
		if (file.is_regular_file()) 
		{
			m_filePaths.push_back(file.path());
		}
	}
}

void BasicFileManager::updateDirectory(const std::filesystem::path& fileDirectory)
{
	initialize(fileDirectory);
	updateFiles();
}

void BasicFileManager::updateDirectory(std::filesystem::path&& fileDirectory)
{
	initialize(std::move(fileDirectory));
	updateFiles();
}

std::filesystem::path BasicFileManager::getFile(const size_t& index) const
{
	return m_filePaths.at(index);
}

std::filesystem::path BasicFileManager::getFile(const std::filesystem::path& filePath) const
{
	const auto searchResult = std::ranges::find_if(m_filePaths, [&filePath](const auto& item)
	{
		return item == filePath;
	});

	if(searchResult == m_filePaths.end())
	{
		throw(std::logic_error("\'filePath\' could not be found."));
	}

	return *searchResult;
}

void BasicFileManager::initialize(const std::filesystem::path& fileDirectory)
{
	if (!std::filesystem::is_directory(fileDirectory))
	{
		throw(std::invalid_argument("The provided path does not lead to a valid directory."));
	}

	m_fileDirectory = fileDirectory;
}

void BasicFileManager::initialize(std::filesystem::path&& fileDirectory)
{
	if (!std::filesystem::is_directory(fileDirectory))
	{
		throw(std::invalid_argument("The provided path does not lead to a valid directory."));
	}

	m_fileDirectory = std::move(fileDirectory);
}