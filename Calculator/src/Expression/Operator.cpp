#include "Operator.h"

namespace Calculator {
	Operator::Associativity::Associativity()
		: associativity(Operator::Associativity::leftToRight) {
	}
	Operator::Associativity::Associativity(bool associativity)
		: associativity(associativity) {
	}

	Operator::Associativity::operator bool() const {
		return associativity;
	}

	Operator::Operator(const std::string& name, const Function& function, int precedence, bool associativity)
		: name(name), function(function), precedence(precedence), associativity(associativity) {
	}

	Operator::Operator(const std::string& name, void* function, int precedence, bool associativity)
		: name(name), function(function, 2), precedence(precedence), associativity(associativity) {
	}
}