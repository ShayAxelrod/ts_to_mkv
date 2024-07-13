#pragma once
#include <string>
#include <filesystem>
#include "File.h"

class Mkv : public File {
public:
	Mkv(const std::filesystem::path& path) : File(path, File::FType::MKV)
	{}
};