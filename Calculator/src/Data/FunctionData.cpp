#include "FunctionData.h"

#include <cmath>

namespace Calculator::FunctionData {

	double add(double x, double y) {
		return x + y;
	}
	double subtract(double x, double y) {
		return x - y;
	}
	double multiply(double x, double y) {
		return x * y;
	}
	double divide(double x, double y) {
		return x / y;
	}
	double pow(double base, double exponent) {
		return std::pow(base, exponent);
	}
}