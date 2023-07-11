#pragma once

#include "sql/Table.h"
#include <tuple>

namespace Calculator::Data {

	/*
	* @brief	sql table which holds the history of the last calculations
	*/
	class History : public SQL::Table {
	public:
		/*
		* @brief	default constructor, does nothing, methods wont work if init() is not called
		*/
		History();
		/*
		* @brief	constructs History table object and creates table in database if not yet created
		* @param	database: SQL::Database in which table should be located
		*/
		History(SQL::Database& database);

		/*
		* @brief	sets database and tables name, creates table in database if not yet created
		* @param	database: SQL::Database in which table should be located
		*/
		virtual void init(SQL::Database& database);

		/*
		* @brief	saves expression and result from calculation in table
		* @param	expression: string_view of expression
		* @param	result: result of expression
		*/
		virtual void add(std::string_view expression, double result);
		/*
		* @brief	gets all saved expressions and results from table
		* @return	vector of all expression and results, in chronological order
		*/
		virtual std::vector<std::pair<std::string, double>> getAll() const;

	protected:
		/*
		* @brief	creates the table in database
		*/
		virtual void create() override;

		/*
		* @brief	gets the lowest id in table
		* @return	lowest id
		*/
		int firstID() const;
		/*
		* @brief	removes all rows in table which are more than "oldest" entrys old
		* @param	oldest: oldest entry that will not be deleted, default 20
		*/
		void removeOld(std::size_t oldest = 20ull);
	};
}