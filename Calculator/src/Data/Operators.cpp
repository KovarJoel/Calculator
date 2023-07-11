#include "Operators.h"
#include "FunctionData.h"

#include <tuple>
#include <vector>

namespace Calculator::Data {

	Operators::Operators() {}

	Operators::Operators(SQL::Database& database) {
		init(database);
	}

	void Operators::init(SQL::Database& database) {
		init(database, "operators");
	}

	bool Operators::init(SQL::Database& database, std::string_view tableName) {
		if (!m_tableName.empty() || tableName.empty())
			return false;

		m_db = database;
		m_tableName = tableName;

		if (exists())
			drop();
		create();
		return true;
	}

	void Operators::create() {
		m_db.execute("CREATE TABLE ? (name TEXT UNIQUE NOT NULL, precedence INTEGER NOT NULL, "
			"associativity INTEGER DEFAULT ?, functionAddress INTEGER)",
			m_tableName, Operator::Associativity::leftToRight);
		
		using asso = Operator::Associativity;
		std::vector<Operator> ops = {
			{"^", FunctionData::pow, 5, asso::rightToLeft},
			{"/", FunctionData::divide, 4, asso::leftToRight},
			{"*", FunctionData::multiply, 3, asso::leftToRight},
			{"-", FunctionData::subtract, 2, asso::leftToRight},
			{"+", FunctionData::add, 1, asso::leftToRight},
		};
		
		for (const auto& op : ops)
			set(op);
	}

	void Operators::set(const Operator& op) {
		if (!has(op.name))
			m_db.execute("INSERT INTO ? (name, precedence, associativity, functionAddress) VALUES(?, ?, ?, ?)",
				m_tableName, op.name, op.precedence, op.associativity, reinterpret_cast<std::size_t>(op.function.getAddress()));
		else
			m_db.execute("UPDATE ? SET precedence = ?, associativity = ?, functionAddress = ? WHERE name = ?",
				m_tableName, op.precedence, op.associativity, reinterpret_cast<std::size_t>(op.function.getAddress()), op.name);
	}

	std::optional<Operator> Operators::get(std::string_view name) const {
		SQL::TableData table = m_db.execute("SELECT * FROM ? WHERE name = ?", m_tableName, name);
		if (table.empty())
			return {};

		SQL::TableData::dataType& data = table.data;

		return Operator{ data["name"].items[0], reinterpret_cast<void*>(std::stoull(data["functionAddress"].items[0])),
			std::stoi(data["precedence"].items[0]), static_cast<bool>(std::stoi(data["associativity"].items[0])) };
	}

	std::vector<std::string> Operators::getNames() const {
		SQL::TableData table = m_db.execute("SELECT name FROM ? ORDER BY precedence DESC", m_tableName);
		if (table.empty())
			return {};
		return table.data["name"].items;
	}
}