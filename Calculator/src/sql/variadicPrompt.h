#pragma once

#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <type_traits>

namespace SQL {
	
	// extends std::is_same to check if any of the arguments is equal to the first
	template <class T, class... Ts>
	struct is_any : std::disjunction<std::is_same<T, Ts>...> {};

	/* 
	* @brief	escapes all ' characters in a string
	* @param	str: string to escape
	* @return	escaped string
	*/
	static std::string escapeString(const std::string& str) {

		std::string s{str};
		std::size_t index{};

		while (true)
		{
			index = s.find('\'', (index == 0) ? 0 : index + 1);
			if (index == std::string::npos)
				break;

			s.replace(index++, 1, "\'\'");
		}

		s = '\'' + s + '\'';	// surround string by '' to tell sql its a string literal

		return s;
	}

	/* 
	* @brief	converts a given parameter to a "std::string" and escapes any ' characters
	* @param	t: argument whichs type has a "std::ostream& operator<<" overload
	* @return	stringified argument
	*/
	template <typename T>
	static std::string toString(const T& t) {
		std::stringstream ss;
		ss << t;

		// escape text-like data
		if (is_any<T, std::string, std::string_view, std::stringstream, const char*>::value)
			return escapeString(ss.str());

		return ss.str();
	}

	/*
	* @brief	base case for recursive variadic function "paramsToStrVec()"
	* @param	t: argument whichs type has a "std::ostream& operator<<" overload
	* @return	"std::vector<std::string>" of given argument
	*/
	template <typename T>
	static std::vector<std::string> paramsToStrVec(const T& t) {
		std::vector<std::string> vec;
		vec.push_back(toString(t));
		return vec;
	}

	/*
	* @brief	concatenates all arguments in a "std::vector<std::string>" recursiv
	* @param	t: argument whichs type has a "std::ostream& operator<<" overload
	* @param	args: remaining arguments
	* @return	"std::vector<std::string>" of given varadic argument list
	*/
	template <typename T, typename... Args>
	static std::vector<std::string> paramsToStrVec(const T& t, Args... args) {
		std::vector<std::string> vec;
		vec.push_back(toString(t));

		std::vector<std::string> rec = paramsToStrVec(args...);

		vec.insert(vec.end(), rec.begin(), rec.end());

		return vec;
	}

	/*
	* @brief	replaces and escapes all placeholders in a prompt with variadic arguments
	* @param	prompt: contains placeholders to substitute
	* @param	placeholder: placeholder to substitute
	* @param	args: arguments to insert in prompot
	* @return	"std::vector<std::string>" of given varadic argument list
	*/
	template <typename... Args>
	void insertParams(std::string& prompt, const std::string& placeholder, Args... args) {
		std::vector<std::string> params = paramsToStrVec(args...);

		for (const auto& param : params) {
			const std::size_t index = prompt.find(placeholder);
			if (index == std::string::npos)		// to much parameters
			{
#ifdef _DEBUG
				__debugbreak();
#endif // _DEBUG
				break;
			}

			prompt.replace(index, placeholder.size(), param);
		}

#ifdef _DEBUG
			if (prompt.find(placeholder) != std::string::npos)		// not enough parameters
				__debugbreak();
#endif // _DEBUG
	}
}