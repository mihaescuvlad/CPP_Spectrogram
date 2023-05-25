#include "BasicFileManager.hpp"

#include <ranges>

namespace stdfs = std::filesystem;

BasicFileManager::BasicFileManager(const stdfs::path& fileDirectory)
{
	initialize(fileDirectory);
	updateFiles();
}

BasicFileManager::BasicFileManager(stdfs::path&& fileDirectory)
{
	initialize(std::move(fileDirectory));
	updateFiles();
}

void BasicFileManager::updateFiles() 
{
	if(stdfs::is_directory(m_fileDirectory) == false)
	{
		return;
	}

	m_filePaths.clear();

	for (const auto& file : stdfs::directory_iterator(m_fileDirectory)) 
	{
		//if (file.is_regular_file()) 
		//{
		//	m_filePaths.push_back(file.path());
		//}

		m_filePaths.push_back(file.path());
	}
}

void BasicFileManager::updateDirectory(const stdfs::path& fileDirectory)
{
	initialize(fileDirectory);
	updateFiles();
}

void BasicFileManager::updateDirectory(stdfs::path&& fileDirectory)
{
	initialize(std::move(fileDirectory));
	updateFiles();
}

stdfs::path BasicFileManager::getParentForCurrentPath() const
{
	return m_fileDirectory.parent_path();
}

stdfs::path BasicFileManager::getCurrentDirectory() const
{
	return absolute(m_fileDirectory);
}

std::vector<stdfs::path> BasicFileManager::getFilesInCurrentDirectory() const
{
	return m_filePaths;
}

uint32_t BasicFileManager::getFileCountInDirectory() const
{
	return static_cast<uint32_t>(m_filePaths.size());
}

stdfs::path BasicFileManager::getFile(const size_t& index) const
{
	return m_filePaths.at(index);
}

stdfs::path BasicFileManager::getFile(const stdfs::path& filePath) const
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

void BasicFileManager::initialize(const stdfs::path& fileDirectory)
{
	if (!stdfs::is_directory(fileDirectory))
	{
		throw(std::invalid_argument("The provided path does not lead to a valid directory."));
	}

	m_fileDirectory = fileDirectory;
}

void BasicFileManager::initialize(stdfs::path&& fileDirectory)
{
	if (!stdfs::is_directory(fileDirectory))
	{
		throw(std::invalid_argument("The provided path does not lead to a valid directory."));
	}

	m_fileDirectory = fileDirectory;
}