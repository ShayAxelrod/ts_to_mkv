#pragma once
#include <string>
#include <memory>
#include <vector>
#include <filesystem>
#include "TsFile.hpp"
#include "MkvFile.hpp"
#include "File.hpp"

class FileFactory {
public:
	static std::vector<std::shared_ptr<File>> getFiles(const std::string& path) {
		std::vector<std::shared_ptr<File>> files;
		for (const auto& file : std::filesystem::directory_iterator(path)) {
			if (!file.is_regular_file())
				continue;
			auto known_file = initFile(file.path());
			if (known_file)
				files.push_back(known_file);
		}
		return files;
	}

	static std::vector<std::shared_ptr<File>> getFiles(const std::vector<std::string>& paths) {
		std::vector<std::shared_ptr<File>> files;
		for (const auto& path : paths) {
			auto files_in_path = getFiles(path);
			files.insert(files.end(), files_in_path.begin(), files_in_path.end());
		}
		return files;
	}

	static std::shared_ptr<File> initFile(const std::filesystem::path& path) {
		const auto& extension = path.extension().string();
		if (extension == ".ts") {
			return std::make_shared<Ts>(path);
		}
		if (extension == ".mkv") {
			return std::make_shared<Mkv>(path);
		}
		else
			return nullptr;
	}
};