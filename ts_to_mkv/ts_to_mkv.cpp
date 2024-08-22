// ts_to_mkv.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>

#include "FfmpegManager.hpp"

using namespace std;
using FFM = FfmpegManager;

int main()
{
	//Option 1:
	FFM::convert_path("D:\\Users\\Axelr\\Downloads\\");

	//Option 2:
	FFM::ConvertableFiles cf = FFM::getFiles("D:\\Users\\Axelr\\Downloads\\");
	FFM::convert(cf);
}