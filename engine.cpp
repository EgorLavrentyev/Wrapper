﻿#include "engine.h"
#include <iostream>
#include <vector>

void Engine::register_command(Wrapper* wrapper, std::string const& command)
{
	if (commands.find(command) != commands.end())
	{
		std::string error = "The following command is already registered: " + command;
		throw std::exception(error.c_str());
	}

	commands[command] = wrapper;
}

int Engine::execute(std::string const& command, std::vector<std::pair<std::string, int>> const& params)
{
	std::map<std::string, Wrapper*>::iterator it;
	if ((it = commands.find(command)) == commands.end())
	{
		std::string error = "The following command has not been registered: " + command;
		throw std::exception(error.c_str());
	}

	return it->second->execute(params);
}
