#pragma once

#include "Database.h"

#include <string>
#include <string_view>
#include <vector>
#include <optional>

namespace SQL {

	/*
	* @brief	base class of a wrapper for to access a table in a sql database
	*/
	class Table {
	public:
		/*
		* @brief	default constructor, does nothing, methods wont work if init() is not called
		*/
		Table();
		/*
		* @brief	constructs BaseTable object and creates table in database if not yet created
		* @param	database: SQL::Database in which table should be located
		* @param	tableName: name of the table in database
		*/
		Table(SQL::Database& database, std::string_view tableName);

		/*
		* @brief	sets database and tables name, creates table in database if not yet created
		* @param	database: SQL::Database in which table should be located
		* @param	tableName: name of the table in database
		* @return	true if table got created or already existed, false if already initialized or tableName is empty
		*/
		virtual bool init(SQL::Database& database, std::string_view tableName);
		/*
		* @brief	checks wheter the table exists in the database or not
		* @return	true if table exists, else false
		*/
		virtual bool exists() const;

		/*
		* @return	returns the entire SQL::Table
		*/
		virtual SQL::TableData getTable() const;

		/*
		* @brief	deletes all elements in talbe
		*/
		virtual void removeAll();

		/*
		* @brief	gets the number of rows in table
		* @return	number of rows
		*/
		virtual int rows() const;
		/*
		* @brief	gets the number of columns in table
		* @return	number of columns
		*/
		virtual int columns() const;

	protected:
		/*
		* @brief	drops the whole table
		*/
		virtual void drop();
		/*
		* @brief	creates the table in database
		*/
		virtual void create() = 0;

	protected:
		std::string m_tableName;
		SQL::Database m_db;
	};

	/*
	* @brief	base class of a wrapper for to access a table in a sql database,
	*			additional methods for a BaseTable which has a column "name"
	*/
	class TableWithName : public Table {
	public:
		/*
		* @brief	checks wheter the table has a row with specified name
		* @param	name: name of the row to search for
		* @return	true if found, else false
		*/
		virtual bool has(std::string_view name) const;
		/*
		* @brief	gets all data in "name" column
		* @return	a vector of all names in table
		*/
		virtual std::vector<std::string> getNames() const;
		/*
		* @brief	removes row wiht specified name from table, if row not found it does nothing
		* @param	name: name of the row
		*/
		virtual void remove(std::string_view name);
	};
}