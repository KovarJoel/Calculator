#pragma once

#include "Command/Commands.h"

#include <string>
#include <string_view>
#include <tuple>

namespace Calculator {
	/*
	* @brief	Calculator Application, should run in infinite loop, gets user input, evaluates it, prints results
	*/
	class Application
	{
	public:
		/*
		* @brief	starts Application, sets locale, initializes dependencies, prints welcome message
		*/
		Application();

		/*
		* @brief	checks wheter the application is running or should stop,
					currently always true since "!exit" calls std::exit() directly
		* @return	true if application should keep running, false otherwise
		*/
		bool isRunning() const;
		/*
		* @brief	gets a prompt from the user via stdin
		*/
		void getPrompt();
		/*
		* @brief	evaluates last prompt
		*/
		void handlePrompt();

	private:
		/*
		* @brief	prints a weclome/help message
		*/
		void initMsg();
		
		/*
		* @brief	splits a mathematical expression at the '=' sign
		* @param	expression: users whole input, '=' and characters before get chopped off
		* @return	name of the variable to assign the expression to
		*/
		std::string splitAssignment(std::string& expression);
		/*
		* @brief	assigns the result of an expression to specified variable, saves result in variable 'ans',
					saves expression and result in history
		* @param	variable: name of the variable
		* @param	value: result of expression
		* @return	true if no variable specified or value got assigned, false if invalid name or reserved variable
		*/
		bool assign(const std::string& variable, double value);

	private:
		Commands m_commands;
		bool m_isRunning;
		std::string m_prompt;
	};
}