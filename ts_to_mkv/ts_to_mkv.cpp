// ts_to_mkv.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>

#include "Files.hpp"

using namespace std;

int main()
{
	vector<shared_ptr<File>> files = FileFactory::getFiles("D:\\Users\\Axelr\\Downloads\\");

	for (const auto& file : files) {
		if (file->getFileType() == File::FType::TS)
			wcout << *file << endl;
	}

}