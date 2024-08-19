#pragma once
#include <string>
#include <filesystem>
#include "File.hpp"

class Mkv : public File {
public:
	Mkv(const std::filesystem::path& path) : File(path, File::FType::MKV)
	{}
};