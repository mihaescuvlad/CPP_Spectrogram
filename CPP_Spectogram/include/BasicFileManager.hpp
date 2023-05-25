#ifndef BASIC_FILE_MANAGER_HPP
#define BASIC_FILE_MANAGER_HPP

#include "Constants.hpp"
#include "IFileManager.hpp"

class BasicFileManager final : public IFileManager
{
private:

	std::filesystem::path m_fileDirectory;
	std::vector<std::filesystem::path> m_filePaths;
public:
	BasicFileManager(const std::filesystem::path& fileDirectory);
	BasicFileManager(std::filesystem::path&& fileDirectory);

	~BasicFileManager() override = default;

	void updateFiles() override;

	void updateDirectory(const std::filesystem::path& fileDirectory) override;
	void updateDirectory(std::filesystem::path&& fileDirectory) override;

	std::filesystem::path getParentForCurrentPath() const override;
	std::filesystem::path getCurrentDirectory() const override;
	std::vector<std::filesystem::path> getFilesInCurrentDirectory() const override;
	uint32_t getFileCountInDirectory() const override;

	std::filesystem::path getFile(const size_t& index) const override;
	std::filesystem::path getFile(const std::filesystem::path& filePath) const override;

	BasicFileManager(const BasicFileManager&) = delete;
	BasicFileManager(BasicFileManager&&) = delete;

	BasicFileManager& operator=(const BasicFileManager&) = delete;
	BasicFileManager& operator=(BasicFileManager&&) = delete;
private:
	void initialize(const std::filesystem::path& fileDirectory);
	void initialize(std::filesystem::path&& fileDirectory);
};

inline std::unique_ptr<IFileManager> makeBasicFileManager(const std::filesystem::path& fileDirectory = Constants::DEFAULT_FILE_PATH)
{
	return std::make_unique<BasicFileManager>(fileDirectory);
}

inline std::unique_ptr<IFileManager> makeBasicFileManager(std::filesystem::path&& fileDirectory)
{
	return std::make_unique<BasicFileManager>(fileDirectory);
}

#endif
