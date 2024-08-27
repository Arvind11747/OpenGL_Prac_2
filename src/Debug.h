#pragma once
#include <iostream>

static class Debug
{
public:
	static void Log(const char* message)
	{
		std::cout << message << std::endl;
	}
};