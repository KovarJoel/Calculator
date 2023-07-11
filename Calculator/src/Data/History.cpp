#include "History.h"

#include <iostream>

namespace Calculator::Data {

	History::History() {}

	History::History(SQL::Database& database) {
		init(database);
	}

	void History::init(SQL::Database& database) {
		SQL::Table::init(database, "history");
	}

	void History::create() {
		m_db.execute("CREATE TABLE ? (id INTEGER PRIMARY KEY, expression TEXT NOT NULL, result REAL NOT NULL)", m_tableName);
	}

	void History::add(std::string_view expression, double result) {
		m_db.execute("INSERT INTO ? (expression, result) VALUES(?, ?)", m_tableName, expression, result);
		removeOld();
	}

	int History::firstID() const {
		return std::stoi(m_db.execute("SELECT id FROM ? ORDER BY id ASC", m_tableName).data["id"].items[0]);
	}

	void History::removeOld(std::size_t oldest) {
		if (rows() > oldest)
			m_db.execute("DELETE FROM ? WHERE id < ? + 1", m_tableName, rows() - oldest);
		m_db.execute("UPDATE ? SET id = id - ? + 1", m_tableName, firstID());
	}

	std::vector<std::pair<std::string, double>> History::getAll() const {
		SQL::TableData table = m_db.execute("SELECT expression, result FROM ? ORDER BY id ASC", m_tableName);

		if (table.empty())
			return {};

		std::vector<std::pair<std::string, double>> history;

		for (std::size_t i = 0; i < table.data["expression"].items.size(); i++)
			history.emplace_back(table.data["expression"].items[i], std::stod(table.data["result"].items[i]));

		return history;
	}
}