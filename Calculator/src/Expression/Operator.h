#pragma once

#include "Function.h"

#include <string>
#include <unordered_map>

namespace Calculator {
	
	/*
	* @brief	wrapper for a mathematical operator (+, -, *, /, ^)
	*/
	class Operator {
	public:
		/*
		* @brief	wrapper for the associativity (left to right or right to left) of a mathematical operator
		*/
		class Associativity {
		public:
			/*
			* @brief	default constructor, sets associativity to left to right
			*/
			Associativity();
			/*
			* @param	associativity: true for left to right, false for right to left
			*/
			Associativity(bool associativity);

			/*
			* @brief	overload of operator bool() to not have to access member
			* @return	true for left to right, false for right to left
			*/
			operator bool() const;
			static constexpr bool leftToRight = true;
			static constexpr bool rightToLeft = false;

		private:
			bool associativity;
		};

	public:
		/*
		* @param	name: symbol of the operator (+, -, *, /, ^)
		* @param	function: function object of associative function for operator (e.g. for operator+ -> double add(double x, double y);)
		* @param	precedence: precedence of operator (higher precedence gets executed earlier)
		* @param	associativity: associativity of operator
		*/
		Operator(const std::string& name, const Function& function, int precedence, bool associativity);
		/*
		* @param	name: symbol of the operator (+, -, *, /, ^)
		* @param	function: void* of associative function for operator (e.g. for operator+ -> double add(double x, double y);)
		* @param	precedence: precedence of operator (higher precedence gets executed earlier)
		* @param	associativity: associativity of operator
		*/
		Operator(const std::string& name, void* function, int precedence, bool associativity);

	public:
		int precedence;
		Associativity associativity;
		std::string name;
		Function function;
	};
}