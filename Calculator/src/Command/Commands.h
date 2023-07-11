#pragma once

#include "Command.h"

#include <string>
#include <string_view>
#include <vector>

namespace Calculator {

	/*
	* @brief	list of executable commands in application
	*/
	class Commands {
	public:
		friend class Command;
	public:
		/*
		* @brief	commands constructor, loads all available commands
		*/
		Commands();

		/*
		* @brief	checks wheter a command exists
		* @param	command: commands name
		* @return	true if it exists, else false
		*/
		bool exists(std::string_view command);
		/*
		* @brief	executes specified command and possible additional arguments
		* @param	command: commands name
		*/
		void execute(std::string_view command);
	
	private:
		/*
		* @brief	creates Command objects and their according functions for all commands
		*/
		void init();
		/*
		* @brief	splits string of parameters, seperated by a '-' into a vector of strings
		* @param	parameters: parameters to split
		* @return	std::vector<std::string> which contains each single argument
		*/
		static std::vector<std::string> splitParameters(std::string_view parameters);

	private:
		inline static std::vector<Command> commands;
	};
}