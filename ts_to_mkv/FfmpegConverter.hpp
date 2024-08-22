#pragma once
#include <chrono>
#include <thread>
#include <memory>
#include <string>
#include "File.hpp"

#include <iostream>

class FfmpegConverter {
public:

	using ConvertableFile = std::shared_ptr<File>;
	
	FfmpegConverter(const ConvertableFile& fsource)
		: m_fsource(fsource)
	{
		//command = f'ffmpeg -i \"{file["path"]}\\{name}.{file["extention"]}\" -c copy \"{file["path"]}\\{name}.mkv\"'
		m_run_command += L"ffmpeg -v quiet -y -vsync 0 -hwaccel cuda -hwaccel_output_format cuda -i \"";
		m_run_command += m_fsource->getPath();
		m_run_command += L"\\";
		m_run_command += m_fsource->getName();
		m_run_command += m_fsource->getExtention();
		m_run_command += L"\"";
		m_run_command += L" -c copy \"";
		m_run_command += m_fsource->getPath();
		m_run_command += L"\\";
		m_run_command += m_fsource->getName();
		m_run_command += L".mkv\"";
	}

	void run() {
		_wsystem(m_run_command.c_str());
	}

	void run_print() {
		std::wcout << m_run_command << std::endl;
	}

protected:
	float m_progress = 0.00;

private:
	const ConvertableFile m_fsource;
	std::wstring m_run_command = L"";
};