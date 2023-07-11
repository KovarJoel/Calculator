#pragma once

namespace Calculator {
	/*
	* @brief	contains basic arithmetic functions for all operators,
	*			which addresses can be taken because there are no overloads or templates
	*/
	namespace FunctionData {
		double add(double x, double y);
		double subtract(double x, double y);
		double multiply(double x, double y);
		double divide(double x, double y);
		double pow(double base, double exponent);
	}
}