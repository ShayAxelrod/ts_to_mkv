#pragma once
#include <string>
#include <filesystem>
#include "File.hpp"

class Ts : public File{
public:
	Ts(const std::filesystem::path& path) : File(path, File::FType::TS)
	{}
};