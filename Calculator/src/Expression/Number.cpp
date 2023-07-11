#include "Number.h"

#include "Data/Data.h"

#include <iostream>
#include <cmath>

namespace Calculator {
	Number::Number()
		: m_val(0.0), m_hasVal(false) {
	}

	Number::Number(const std::string& expression)
		: m_val(0.0), m_hasVal(false) {
		std::optional<double> value = calculate(expression);
		
		if (!value)
			return;

		m_val = value.value();
		m_hasVal = true;
	}

	Number::Number(double value)
		: m_val(value), m_hasVal(true) {
	}

	void Number::operator=(const std::string& expression) {
		Number other(expression);
		m_val = other.m_val;
		m_hasVal = other.m_hasVal;
	}

	Number::operator double() const {
		return m_val;
	}

	bool Number::hasValue() const {
		return m_hasVal;
	}

	std::optional<double> Number::calculate(const std::string& expression) {
		if (expression.empty())
			return {};
		std::string expr{ expression };
		insertVariables(expr);
		try {
			while (calcInnermostExpr(expr));
		}
		catch (const std::invalid_argument& e) {
			throw e;
			return {};
		}
		
		double value = std::stod(expr);

		if (std::isnan(value))
			throw std::invalid_argument("NOT A NUMBER");
		if (std::isinf(value))
			throw std::invalid_argument("INFINITE");

		return value;
	}

	bool Number::calcInnermostExpr(std::string& expression) {
		if (isNumber(expression))
			return false;

		std::size_t left{}, right{};
		left = expression.rfind('(');
		right = expression.find(')', left);
		std::string innermost;

		if (left == std::string::npos && right == std::string::npos) {
			innermost = expression;
			calcExpr(innermost);
			expression = innermost;

			if (!isNumber(expression))
				throw std::invalid_argument("SYNTAX ERROR, UNEXPECTED OR MISSING SYMBOL");

			return false;
		}
		else if (left == std::string::npos || right == std::string::npos)
			throw std::invalid_argument("SYNTAX ERROR, INVALID PARENTHESES");
		else {
			innermost = { expression.substr(left + 1, right - (left + 1)) };
			calcExpr(innermost);
			expression.replace(left, right - left + 1, innermost);
			return true;
		}
	}

	void Number::calcExpr(std::string& expression) {
		std::vector<std::string> ops = Data::getOps().getNames();

		for (const auto& op : ops) {
			std::size_t index{};
			while (true) {
				if (isNumber(expression))
					return;

				Operator::Associativity as = Data::getOps().get(op).value().associativity;
				if (as == Operator::Associativity::leftToRight)
					index = expression.find(op);
				else
					index = expression.rfind(op);

				ignoreSignedUnsigned(expression, op, index);

				if (index == std::string::npos)
					break;

				std::pair<double, std::size_t> previous = getPreviousNum(expression, index);
				std::pair<double, std::size_t> next = getNextNum(expression, index);

				// input like "*3", no first value for operator *
				if (previous.second == std::string::npos || next.second == std::string::npos)
					throw std::invalid_argument("SYNTAX ERROR, UNEXPECTED OR MISSING SYMBOL");

				double val = Data::getOps().get(op).value().function(previous.first, next.first);

				expression.replace(previous.second, next.second + 1 - previous.second, std::to_string(val));
			}
		}
	}

	bool Number::isNumber(const std::string& expression, std::size_t start, std::size_t end) {
		const std::string nr = expression.substr(start, end - start);
		if (nr.empty())
			return false;
		char* endStr;
		static_cast<void>(std::strtod(nr.c_str(), &endStr));
		return *endStr == '\0';
	}

	std::pair<double, std::size_t> Number::getNextNum(const std::string& expression, std::size_t index) {
		for (std::size_t i = expression.size() - 1; i > index; i--) {
			if (isNumber(expression, index + 1, i + 1))
				return { std::stod(expression.substr(index + 1, i + 1)), i};
		}
		return { 0.0, std::string::npos };
	}
	std::pair<double, std::size_t> Number::getPreviousNum(const std::string& expression, std::size_t index) {
		for (std::size_t i = 0; i < index; i++) {
			if (!isNumber(expression, i, index))
				continue;
			if (expression[i] == '-' || expression[i] == '+')
				if (i && isNumber(expression, i - 1, i))	// 1-2+3  -->  -2+3  -->  1 is Number
					continue;
			return { std::stod(expression.substr(i, index)), i};
		}
		return { 0.0, std::string::npos };
	}

	void Number::ignoreSignedUnsigned(const std::string& expression, const std::string& op, std::size_t& index) {
		// ignores operators +- when used as signed/unsigned indicator
		Operator::Associativity as = Data::getOps().get(op).value().associativity;
		while (op == "+" || op == "-") {
			if (index == std::string::npos)
				break;
			if (!index || (index && Data::getOps().has({ &expression[index - 1], 1 }))) {
				if (as == Operator::Associativity::leftToRight) {
					index = expression.find(op, index + 1);
					continue;
				}
				else {
					index = expression.rfind(op, !index ? index : index - 1);
					continue;
				}
			}
			break;
		}
	}

	void Number::insertVariables(std::string& expression) {
		const std::vector<std::string> vars = Data::getVars().getNames();

		for (const auto& var : vars) {
			std::size_t index = 0;
			while (true) {
				index = expression.find(var, index);
				if (index == std::string::npos)	// if not found
					break;
				if (index)	// if in larger name/number
					if (std::isalpha(expression[index - 1]) || std::isdigit(expression[index - 1])) {
						index++;
						continue;
					}
				if (index + var.size() < expression.size())	// if in larger name/number
					if (std::isalpha(expression[index + var.size()]) || std::isdigit(expression[index + var.size()])) {
						index++;
						continue;
					}

				expression.replace(index, var.size(), std::to_string(Data::getVars().get(var).value()));
			}
		}
	}
}