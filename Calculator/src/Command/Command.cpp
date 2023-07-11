#include "Command.h"

namespace Calculator {
	Command::Command(std::string_view name, std::string_view description, const funcType& function)
		: name(name), description(description), function(function) {
#ifdef _DEBUG
		if (!function)
			__debugbreak();
#endif // _DEBUG
	}
}