#pragma once
#include "Wrapper.h"
#include <string>
#include <map>

class Engine
{
public:
	void register_command(Wrapper* wrapper, std::string command);
	int execute(std::string command, const std::vector<std::pair<std::string, int>>& params);
private:
	std::map<std::string, Wrapper*> commands;
};