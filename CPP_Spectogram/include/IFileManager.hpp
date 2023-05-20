#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <filesystem>
#include <memory>

class IFileManager 
{
public:
	virtual ~IFileManager() = default;

	virtual void updateFiles() = 0;
	virtual void updateDirectory(const std::filesystem::path&) = 0;
	virtual void updateDirectory(std::filesystem::path&&) = 0;

	virtual std::filesystem::path getFile(const size_t&) const = 0;
	virtual std::filesystem::path getFile(const std::filesystem::path&) const = 0;
};

std::unique_ptr<IFileManager> makeBasicFileManager(const std::filesystem::path&);
std::unique_ptr<IFileManager> makeBasicFileManager(std::filesystem::path&&);

#endif