#include "Application.h"

#include "Data/Data.h"
#include "Expression/Number.h"

#include <iostream>
#include <iomanip>
#include <locale>
#include <algorithm>

namespace Calculator {

	Application::Application()
		:m_isRunning(false), m_prompt() {
		std::cout.imbue(std::locale("en_US"));	// for printing numbers, decimal point is '.', seperator for 10^3 is ','

		Data::init();

		initMsg();

		m_isRunning = true;
	}

	bool Application::isRunning() const {
		return m_isRunning;
	}

	void Application::initMsg() {
		std::cout << "+------------------------------------+" << '\n';
		std::cout << "| Welcome to my Calculator!          |" << '\n';
		std::cout << "|                                    |" << '\n';
		std::cout << "| Write some expression to calculate |" << '\n';
		std::cout << "| Type !help for more information    |" << '\n';
		std::cout << "+------------------------------------+" << '\n';
		std::cout << std::endl;
	}

	void Application::getPrompt() {
		std::getline(std::cin, m_prompt);
		m_prompt.erase(std::remove_if(m_prompt.begin(), m_prompt.end(), ::isspace), m_prompt.end());
	}

	void Application::handlePrompt() {
		if (!m_prompt.empty() && m_prompt[0] == '!') {
			m_commands.execute(m_prompt);
			return;
		}

		std::string var = splitAssignment(m_prompt);
		Number nr;
		try {
			nr = m_prompt;
		}
		catch (const std::invalid_argument& e) {
			std::cout << '\t' << e.what() << std::endl;
		}

		if (!nr.hasValue())
			return;
		std::cout << "\t-> " << nr << std::endl;

		if (!assign(var, nr))
			std::cout << "\tINVALID VARIABLE NAME" << std::endl;
	}

	std::string Application::splitAssignment(std::string& expression) {
		std::size_t assignIndex = expression.find('=');
		if (assignIndex == std::string::npos || expression.find('=', assignIndex + 1) != std::string::npos) {
			return {};
		}

		std::string var = expression.substr(0, assignIndex);
		expression.erase(0, assignIndex + 1);
		return var;
	}

	bool Application::assign(const std::string& variable, double value) {
		Data::getVars().setAny("ans", value);
		Data::getHistory().add(m_prompt, value);

		if (variable.empty())
			return true;		// not exactly assign to a user defined variable but to "ans" anyways whats everything that was requested

		if (std::find_if_not(variable.begin(), variable.end(), ::isalpha) != variable.end())
			return false;		// invalid name for the variable

		for (const std::string& op : Data::getOps().getNames())
			if (variable == op)
				return false;

		if (!Data::getVars().set(variable, value))
			return false;
		return true;
	}
}