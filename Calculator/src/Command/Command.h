#pragma once

#include <string>
#include <string_view>
#include <functional>

namespace Calculator {

	/*
	* @brief	command which can be run from inside the application
	*/
	class Command {
		/*
		* @brief	type of each commands function
		* @param	parameters: std::string_view of additional input when executing command
		* @return	void
		*/
		using funcType = std::function<void(std::string_view parameters)>;

	public:
		/*
		* @brief	creates a command
		* @param	name: name of the command
		* @param	description: help description for that command
		* @param	function: function which will be called when command is executed
		*/
		Command(std::string_view name, std::string_view description, const funcType& function);

	public:
		const std::string name;
		const std::string description;
		const funcType function;
	};
}