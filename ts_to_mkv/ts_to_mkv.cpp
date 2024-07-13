// ts_to_mkv.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Files.h"

using namespace std;

int main()
{
	vector<string> paths = {
		"D:\\Users\\Axelr\\Downloads\\cTS00021.ts",
		"D:\\Users\\Axelr\\Downloads\\cTS00022.ts",
		"D:\\Users\\Axelr\\Downloads\\cMKV00021.mkv",
		"D:\\Users\\Axelr\\Downloads\\cMP400021.mp4"
	};
	vector<shared_ptr<File>> files = FileFactory::getFiles("D:\\Users\\Axelr\\Downloads\\test");

	/*for (const auto& full_path : paths) {
		auto file = FileFactory::initFile(full_path);
		if (file)
			files.push_back(FileFactory::initFile(full_path));
	}*/

	for (const auto& file : files) {
		cout << *file << endl;
	}
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
