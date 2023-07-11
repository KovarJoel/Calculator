#pragma once

#include <limits>

#define UNPACK(Args) typename unpack<Args>::type...
template <typename T>
struct unpack { using type = T; };

namespace Calculator {
	/*
	* @brief	Function object for mathematical functions, variable arguments, not type safe,
				does not enforce or check correct amount or type of arguments
	*/
	class Function {
	public:
		/*
		* @brief	default constructor, sets function to nullptr
		*/
		Function();
		/*
		* @brief	constructs Function object
		* @param	function: void* of function, overloaded or templated function might not work
		* @param	arity: amount of parameters to expect for specified function, currently not in use
		*/
		Function(void* function, int arity);

		/*
		* @brief	checks wheter a function is set (pointer to it is not nullptr)
		* @return	true if it holds a valid pointer, else false
		*/
		operator bool() const;

		/*
		* @brief	calls underlying function if not nullptr with variable args, should match arity and types which is not enforced!
		*			only use it if you know what it does and how the Function object got created!
		* @param	args...: variable arguments
		* @return	result of function call, if function is nullptr: quiet_NaN
		*/
		template <typename ...Args>
		double operator() (const Args&... args) const {
			if (!m_func)
				return std::numeric_limits<double>::quiet_NaN();

			auto func = reinterpret_cast<double(*)(UNPACK(Args))>(m_func);
			return func(args...);
		}

		/*
		* @return void* of the function
		*/
		void* getAddress() const;

	public:
		const int arity;

	private:
		void* m_func;
	};
}