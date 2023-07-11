#include "Data.h"

namespace Calculator::Data {
	inline static SQL::Database s_db;
	inline static Variables s_vars;
	inline static Operators s_ops;
	inline static History s_history;

	void init() {
		s_db.open("calculator.db");

		s_vars.init(s_db);
		s_ops.init(s_db);
		s_history.init(s_db);
	}

	Variables& getVars() {
		return s_vars;
	}

	Operators& getOps() {
		return s_ops;
	}

	History& getHistory() {
		return s_history;
	}
}