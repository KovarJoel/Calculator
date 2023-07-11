#pragma once

#include "variadicPrompt.h"
#include "TableData.h"

#include <string>
#include <sqlite/sqlite3.h>

namespace SQL {

	/*
	* @brief	simple sqlite database wrapper
	*/
	class Database {
	public:
		Database();
		/*
		* @brief	opens specified database
		* @param	path: absolut path of database
		*/
		Database(const std::string& path);
		/*
		* @brief	closes database and frees up memory
		*/
		~Database();

		/*
		* @brief	opens specified database
		* @param	path: absolut path of database
		*/
		void open(const std::string& path);
		/*
		* @brief	closes current database
		*/
		void close();

		/*
		* @brief	returns whether a database is currently opened or not
		* @return	true if opened, else false
		*/
		operator bool() const;

		/*
		* @brief	lets you execute a command on the sqlite database with variadic arguments
		* @param	command: sqlite command to be executed
		* @param	args: variadic arguments to be inserted in the command at each "?", strings will be escaped
		* @return	sql table with found data, empty table for eg "CREATE TABLE ..."
		*/
		template <typename ...Args>
		TableData execute(const std::string& command, Args... args) const {
			std::string fullCommand{command};
			insertParams(fullCommand, "?", args...);

			return execute(fullCommand);
		};

		/*
		* @brief	lets you execute a command on the sqlite database, base-case for variadic function overload
		* @param	command: sqlite command to be executed
		* @return	sql table with found data, empty table for eg "INSERT ..."
		*/
		TableData execute(const std::string& command) const;

	private:
		sqlite3* m_db;
	};
}