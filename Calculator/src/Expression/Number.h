#pragma once

#include <string>
#include <optional>
#include <utility>

namespace Calculator {

	/*
	* @brief	can calculate a number from an expression (string),
				holds a number (double) and a boolean indicating wether the number is valid or not
	*/
	class Number
	{
	public:
		/*
		* @brief	default constructor, hasValue is false
		*/
		Number();
		/*
		* @brief	calculates a value from an expression string, if the string doesnt evaluate to a number hasValue is false
		* @param	expression: std::string of an mathematical expression
		* @throw	std::invalid_argument if calculation failed because of a syntax error, or result is either NaN or inf
		*/
		Number(const std::string& expression);
		/*
		* @brief	initializes number to specified value
		* @param	value: already calculated double
		*/
		Number(double value);
		/*
		* @brief	calculates a value from an expression string, if the string doesnt evaluate to a number hasValue is false
		* @param	expression: std::string of an mathematical expression
		* @throw	std::invalid_argument if calculation failed because of a syntax error, or result is either NaN or inf
		*/
		void operator=(const std::string& expression);

		/*
		* @brief	returns held number
		* @return	value of Number or 0.0 if hasValue = false
		*/
		operator double() const;
		/*
		* @brief	checks wheter Number object holds a set value
		* @return	true if valid, else false
		*/
		bool hasValue() const;

	private:
		/*
		* @brief	calculates a value from a full expression string
		* @param	expression: std::string of an mathematical expression
		* @return	optional<double>, optional has value if calculation was success
		* @throw	std::invalid_argument if calculation failed because of a syntax error, or result is either NaN or inf
		*/
		static std::optional<double> calculate(const std::string& expressioin);
		/*
		* @brief	creates multiple expression without parentheses which get calculated,
					changes specified expression to a string of the resulting value,
					needs to be called as long as there are parentheses
		* @param	expression: std::string of an mathematical expression
		* @return	true if it is still calculating, false if it is done ore a syntax error occured
		* @throw	std::invalid_argument if calculation failed because of a syntax error
		*/
		static bool calcInnermostExpr(std::string& expression);
		/*
		* @brief	calculates a mathematical expression without parentheses
		* @param	expression: std::string of an mathematical expression
		* @throw	std::invalid_argument if calculation failed because of a syntax error
		*/
		static void calcExpr(std::string& expression);
		/*
		* @brief	checks wheter a specified expression (or its substring) is fully convertible to a double
		* @param	expression: std::string of an mathematical expression
		* @param	start: first index to consider as part of the expression to check
		* @param	end: first index which is not considered as part of the expression to check 
		* @return	true if specified expression is fully convertible to a double with std::strtod(), else false
		*/
		static bool isNumber(const std::string& expression, std::size_t start = 0, std::size_t end = std::string::npos);
		/*
		* @brief	returns the following number after a specified index (of an mathematical operator)
		* @param	expression: std::string of an mathematical expression
		* @param	index: index of an operator
		* @return	pair of following numbers value and last index which is part of that number,
		*			0.0 and std::string::npos if no following number exists
		*/
		static std::pair<double, std::size_t> getNextNum(const std::string& expression, std::size_t index);
		/*
		* @brief	returns the previous number before a specified index (of an mathematical operator),
		*			the sign of a number counts as part of it
		*			(e.g. -12 or +12 would count as -12 and +12 and not as -12 and 12)
		*			examples: 3++12 -> 3 + (12), (+12) -> 12, 2^-12 -> 2^(-12)
		* @param	expression: std::string of an mathematical expression
		* @param	index: index of an operator
		* @return	pair of previous numbers value and fist index which is part of that number,
		*			0.0 and std::string::npos if no following number exists
		*/
		static std::pair<double, std::size_t> getPreviousNum(const std::string& expression, std::size_t index);
		/*
		* @brief	updates specified index to next operator if specified operator is actually a signed/unsigned indicator
		* @param	expression: std::string of an mathematical expression
		* @param	op: mathematical operator 
		* @param	index: index of specified operator, can get updated
		*/
		static void ignoreSignedUnsigned(const std::string& expression, const std::string& op, std::size_t& index);
		/*
		* @brief	replaces all variables in specified expression with corresponding values from database
		* @param	expression: std::string of an mathematical expression
		*/
		static void insertVariables(std::string& expression);

	private:
		double m_val;
		bool m_hasVal;
	};
}