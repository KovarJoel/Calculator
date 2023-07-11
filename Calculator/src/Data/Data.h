#pragma once

#include "Variables.h"
#include "Operators.h"
#include "History.h"

namespace Calculator::Data {

	/*
	* @brief	initializes the database for tables: variables, operators, history and creates static objects for each table
	*/
	void init();

	/*
	* @return	Variables& of a static variables table object
	*/
	Variables& getVars();
	/*
	* @return	Operators& of a static operators table object
	*/
	Operators& getOps();
	/*
	* @return	History& of a static history table object
	*/
	History& getHistory();
}