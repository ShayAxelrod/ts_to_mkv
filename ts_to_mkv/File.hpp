#pragma once
#include <ostream>
#include <string>
#include <filesystem>
#include "Sizes.hpp"

class File {
public:
	enum class FType
	{
		NO_INIT = 0,
		MKV,
		TS,
	};

	File(const std::filesystem::path& fs_path, const FType& f_type = FType::NO_INIT)
		: m_path(fs_path.parent_path().wstring()), m_name(fs_path.stem().wstring()),
		m_ext(fs_path.extension().string()),
		m_size(std::filesystem::file_size(fs_path)),
		m_fs_file_path(fs_path),
		m_file_type(f_type)
	{}

	void setFileType(const FType& type) {
		m_file_type = type;
	}	
	FType getFileType() const {
		return m_file_type;
	}

	bool operator==(const File& other) const {
		return m_fs_file_path == other.m_fs_file_path;
	}

	friend std::wostream& operator<<(std::wostream& out, const File::FType & type);
	friend std::wostream& operator<<(std::wostream& out, const File& file);

protected:
	std::wstring m_path = L"";
	std::wstring m_name = L"";
	std::string m_ext = "";
	Size::Bits m_size = 0;
	std::filesystem::path m_fs_file_path = "";
	FType m_file_type = FType::NO_INIT;

private:
};

std::wostream& operator<<(std::wostream& out, const File::FType& type) {
	switch (type) {
	case File::FType::NO_INIT:
		out << "NO_INIT";
		break;
	case File::FType::MKV:
		out << "MKV";
		break;
	case File::FType::TS:
		out << "TS";
		break;
	}	
	return out;
}

std::wostream& operator<<(std::wostream& out, const File& file) {
	out << file.m_file_type << "\t: " << file.m_name << " (" << file.m_size << ")" << "\t[" << file.m_path << "]";
	return out;
}