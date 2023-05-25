#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <filesystem>
#include <memory>

#include "Constants.hpp"

namespace stdfs = std::filesystem;

class IFileManager 
{
public:
	virtual ~IFileManager() = default;
	IFileManager() = default;

	virtual void updateFiles() = 0;
	virtual void updateDirectory(const stdfs::path&) = 0;
	virtual void updateDirectory(stdfs::path&&) = 0;

	virtual stdfs::path getParentForCurrentPath() const = 0;
	virtual stdfs::path getCurrentDirectory() const = 0;
	virtual std::vector<stdfs::path> getFilesInCurrentDirectory() const = 0;
	virtual uint32_t getFileCountInDirectory() const = 0;

	virtual stdfs::path getFile(const size_t&) const = 0;
	virtual stdfs::path getFile(const stdfs::path&) const = 0;

	IFileManager(const IFileManager&) = delete;
	IFileManager(IFileManager&&) = delete;

	IFileManager& operator=(const IFileManager&) = delete;
	IFileManager& operator=(IFileManager&&) = delete;
};

std::unique_ptr<IFileManager> makeBasicFileManager(const stdfs::path&);
std::unique_ptr<IFileManager> makeBasicFileManager(stdfs::path&&);

#endif