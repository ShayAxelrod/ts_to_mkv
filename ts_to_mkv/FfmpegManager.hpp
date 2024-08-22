#pragma once
#include <vector>
#include <memory>
#include <filesystem>
#include "ThreadPool.hpp"
#include "FileFactory.hpp"
#include "FfmpegConverter.hpp"

struct FfmpegManager {
	using ConvertableFiles = std::vector<FfmpegConverter::ConvertableFile>;
	using fsPath = std::filesystem::path;

	FfmpegManager() = delete;

	static ConvertableFiles getFiles(const fsPath& path) {
		return FileFactory::getFiles(path);
	}

	static void convert(const ConvertableFiles& files) {
		ThreadPool tp;
		tp.enable();
		for (const auto& file : files) {
			FfmpegConverter fc(file);
			tp.queueTask([fc]() mutable { fc.run(); });
		}
		tp.disable();
	}

	static void convert_path(const fsPath& path) {
		convert(getFiles(path));
	}
};