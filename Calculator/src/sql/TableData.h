#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <tuple>

namespace SQL {

	/*
	* @brief	stuct for each column in a table, holds all elements and the length of
				the longest string in either column header or elements
	*/
	struct Column {
		int maxLength;
		std::vector<std::string> items;
	};

	/*
	* @brief	SQL Table returned from a query
	*/
	class TableData {
	public:									// header
		using dataType = std::unordered_map<std::string, Column>;

		/*
		* @brief	checks wether the table contains data or not
		* @return	true if empty, else false
		*/
		bool empty() const;
		/*
		* @brief	deletes all the data in the table
		*/
		void clear();
		/*
		* @brief	prints the tables data formatted to the console
		*/
		void print() const;
		/*
		* @return	number of columns of the table
		*/
		int columns() const;
		/*
		* @return	number of rows of the table
		*/
		int rows() const;

	public:
		dataType data;

	private:
		void printHeader() const;
		void printBody() const;
		void printSeperator() const;

	private:
		static constexpr int paddingWidth = 3;

		/*
		* @brief	callback function called by the sqlite api when querying
		*/
		friend int callback(void* NotUsed, int argc, char** argv, char** azColName);
	};
}