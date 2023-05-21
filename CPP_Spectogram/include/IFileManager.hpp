#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <filesystem>
#include <memory>

#include "Constants.hpp"

class IFileManager 
{
public:
	virtual ~IFileManager() = default;
	IFileManager() = default;

	virtual void updateFiles() = 0;
	virtual void updateDirectory(const std::filesystem::path&) = 0;
	virtual void updateDirectory(std::filesystem::path&&) = 0;

	virtual std::filesystem::path getCurrentDirectory() const = 0;
	virtual uint32_t getFileCountInDirectory() const = 0;

	virtual std::filesystem::path getFile(const size_t&) const = 0;
	virtual std::filesystem::path getFile(const std::filesystem::path&) const = 0;

	IFileManager(const IFileManager&) = delete;
	IFileManager(IFileManager&&) = delete;

	IFileManager& operator=(const IFileManager&) = delete;
	IFileManager& operator=(IFileManager&&) = delete;
};

std::unique_ptr<IFileManager> makeBasicFileManager(const std::filesystem::path&);
std::unique_ptr<IFileManager> makeBasicFileManager(std::filesystem::path&&);

#endif