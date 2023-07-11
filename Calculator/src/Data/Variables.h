#pragma once

#include "sql/Table.h"

namespace Calculator::Data {

	/*
	* @brief	sql table which holds all variables used for the calculator
	*/
	class Variables : public SQL::TableWithName {
	public:
		/*
		* @brief	default constructor, does nothing, methods wont work if init() is not called
		*/
		Variables();
		/*
		* @brief	constructs Variables table object and creates table in database if not yet created
		* @param	database: SQL::Database in which table should be located
		*/
		Variables(SQL::Database& database);

		/*
		* @brief	sets database and tables name, creates table in database if not yet created
		* @param	database: SQL::Database in which table should be located
		*/
		virtual void init(SQL::Database& database);

		/*
		* @brief	saves or updates a not reserved variable in table
		* @param	name: name of variable
		* @param	value: value of variable
		* @return	true if variable got set, else (if variable is reserved) false 
		*/
		virtual bool set(std::string_view name, double value);
		/*
		* @brief	gets a variable from table
		* @param	name: name of variable
		* @return	optional value of variable, does not hold value if variable is not in table
		*/
		virtual std::optional<double> get(std::string_view name) const;

		/*
		* @brief	deletes a not reserved variable from table, if name not found it does nothing
		* @param	name: name of variable
		*/
		virtual void remove(std::string_view name) override;
		/*
		* @brief	deletes all not reserved variables form table
		*/
		virtual void removeAll() override;

		/*
		* @brief	checks wether a variable is reserved or not
		* @param	name: name of variable
		* @return	true if it is reserved, else false
		*/
		virtual bool isReserved(std::string_view name) const;
		/*
		* @brief	saves or updates a variable in table, reserved as well as unreserved
		* @param	name: name of variable
		* @param	value: value of variable
		*/
		virtual void setAny(std::string_view name, double value);
		/*
		* @brief	deletes a variable from table, reserved as well as unreserved, if name not found it does nothing
		* @param	name: name of variable
		*/
		virtual void removeAny(std::string_view name);
		/*
		* @brief	deletes all variables form table, reserved as well as unreserved
		*/
		virtual void removeAllAny();

	protected:
		/*
		* @brief	creates the table in database
		*/
		virtual void create() override;
	};
}