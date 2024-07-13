#pragma once
#include <string>
#include <filesystem>
#include "File.h"

class Ts : public File{
public:
	Ts(const std::filesystem::path& path) : File(path, File::FType::TS)
	{}
};