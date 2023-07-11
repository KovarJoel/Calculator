#include "Function.h"

namespace Calculator {
	Function::Function()
		: m_func(nullptr), arity(0) {
	};

	Function::Function(void* function, int arity)
		: m_func(function), arity(arity) {
	}

	Function::operator bool() const {
		return m_func != nullptr;
	}

	void* Function::getAddress() const {
		return m_func;
	}
}