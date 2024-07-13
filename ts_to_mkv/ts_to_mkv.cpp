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
	vector<shared_ptr<File>> files = FileFactory::getFiles("D:\\Users\\Axelr\\Downloads\\test");

	for (const auto& file : files) {
		cout << *file << endl;
	}
	
}