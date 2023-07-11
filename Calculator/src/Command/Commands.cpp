#include "Commands.h"

#include "../Data/Data.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

#define delimiter "-"
#define newLineStart "\t-  "

namespace Calculator {

	Commands::Commands() {
		init();
	}

	bool Commands::exists(std::string_view command) {
		for (const auto& c : commands)
			if (c.name == command)
				return true;
		return false;
	}

	void Commands::execute(std::string_view command) {
		if (command.empty())
			return;

		const std::size_t firstDelimiter = command.find(delimiter);
		std::string_view function, parameters;
		constexpr char prefix = '!';
		if (command[0] == prefix)
			function = command.substr(1, firstDelimiter - 1);
		else
			function = command.substr(0, firstDelimiter - 1);

		if (firstDelimiter != std::string_view::npos)
			parameters = command.substr(firstDelimiter);

		for (const auto& c : commands) {
			if (c.name == function) {
				c.function(parameters);
				return;
			}
		}

		// if no other function was called (invalid command), display default help page
		commands[0].function("");
	}

	void Commands::init() {
		if (!commands.empty())
			return;

		// keep "help" at 0
		commands.emplace_back("help", "shows this help page", [](std::string_view parameters) {
			for (const auto& c : commands)
				std::cout << newLineStart << std::setw(30) << std::left << c.name << c.description << std::endl;
		});

		commands.emplace_back("clear", "clears the screen", [](std::string_view parameters) {
			std::system("cls");
		});
		commands.emplace_back("exit", "exits the program", [](std::string_view parameters) {
			std::exit(0);
		});
		commands.emplace_back("vars",
			"prints all variables"
			"\n\t" newLineStart "vars" delimiter "del" delimiter "<name>" "\t " "deletes variable <name>"
			"\n\t" newLineStart "vars" delimiter "del" "\t\t " "deletes all variables",
			[](std::string_view parameters) {
				std::vector<std::string> params = splitParameters(parameters);
				if (params.empty())
					for (const auto& var : Data::getVars().getNames())
						std::cout << newLineStart << var << ": " << Data::getVars().get(var).value() << '\n';
				else if (params.size() == 1 && params[0] == "del")
					Data::getVars().removeAll();
				else if (params.size() == 2 && params[0] == "del")
					Data::getVars().remove(params[1]);
		});
		commands.emplace_back("ops", "prints all operators", [](std::string_view parameters) {
			for (const auto& op : Data::getOps().getNames())
				std::cout << newLineStart << op << '\n';
		});
		commands.emplace_back("history", "prints the last calculations", [](std::string_view parameters) {
			for (const auto& [expression, result] : Data::getHistory().getAll())
				std::cout << newLineStart << std::setw(30) << std::left << expression << " " << std::setw(15) << result << '\n';
		});
	}

	std::vector<std::string> Commands::splitParameters(std::string_view parameters) {
		std::string str{parameters};
		std::vector<std::string> params;
		std::size_t index;

		while (true) {
			index = str.find(delimiter);
			if (index == std::string_view::npos)
				break;
			if (index == 0)
				index = str.find(delimiter, index + 1);

			params.emplace_back(str.substr(1, index - 1));
			str.erase(0, index);
		}

		return params;
	}
}