#pragma once
#include "Wrapper.h"
#include <string>
#include <map>

class Engine
{
public:
	Engine() = default;
	Engine(Engine const&) = delete;
	Engine& operator =(Engine const&) = delete;
	Engine(Engine&&) = default;
	Engine& operator =(Engine&&) = default;
	~Engine() = default;
	void register_command(Wrapper* wrapper, std::string const& command);
	int execute(std::string const& command, std::vector<std::pair<std::string, int>> const& params);
private:
	std::map<std::string, Wrapper*> commands;
};