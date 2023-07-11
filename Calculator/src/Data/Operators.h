#pragma once

#include "sql/Table.h"
#include "Expression/Operator.h"

namespace Calculator::Data {

	/*
	* @brief	sql table which holds all operators used for the calculator, don't ask why I save this on a disk I don't know eiter
	*/
	class Operators : public SQL::TableWithName {
	public:
		/*
		* @brief	default constructor, does nothing, methods wont work if init() is not called
		*/
		Operators();
		/*
		* @brief	constructs Operators table object and creates table in database if not yet created
		* @param	database: SQL::Database in which table should be located
		*/
		Operators(SQL::Database& database);

		/*
		* @brief	sets database and tables name, creates table in database if not yet created
		* @param	database: SQL::Database in which table should be located
		*/
		virtual void init(SQL::Database& database);

		/*
		* @brief	saves or updates an operator in table
		* @param	op: operator to insert/update in table
		*/
		virtual void set(const Operator& op);
		/*
		* @brief	gets an operator from table
		* @param	name: name of operator
		* @return	optional operator, does not hold value if operator is not in table
		*/
		virtual std::optional<Operator> get(std::string_view name) const;
		/*
		* @brief	gets all data in "name" column, overloaded because of sorting the operators by precedence
		* @return	a vector of all names of the operators, sorted by precedence descending
		*/
		virtual std::vector<std::string> getNames() const override;

	protected:
		/*
		* @brief	creates the table in database
		*/
		virtual void create() override;

		/*
		* @brief	sets database and tables name, drops old table in database and creates table again,
		*			overloaded because memory addresses of functions corresponding to operators change each time
		* @param	database: SQL::Database in which table should be located
		* @param	tableName: name of the table in database
		* @return	true if table got created, false if already initialized or tableName is empty
		*/
		virtual bool init(SQL::Database& database, std::string_view tableName) override;
	};
}