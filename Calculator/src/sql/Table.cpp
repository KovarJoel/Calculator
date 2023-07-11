#pragma once

#include "Table.h"

#include <string>
#include <string_view>
#include <vector>
#include <optional>

namespace SQL {

	Table::Table() {}

	Table::Table(SQL::Database& database, std::string_view tableName) {
		init(database, tableName);
	}

	bool Table::init(SQL::Database& database, std::string_view tableName) {
		if (!m_tableName.empty() || tableName.empty())
			return false;

		m_db = database;
		m_tableName = tableName;

		if (!exists())
			create();
		return true;
	}

	bool Table::exists() const {
		return !m_db.execute("SELECT * FROM sqlite_schema WHERE name = ? ", m_tableName).empty();
	}

	SQL::TableData Table::getTable() const {
		return m_db.execute("SELECT * FROM ?", m_tableName);
	}

	void Table::removeAll() {
		m_db.execute("DELETE FROM ?", m_tableName);
	}
	
	void Table::drop() {
		m_db.execute("DROP TABLE ?", m_tableName);
	}

	int Table::rows() const {
		return std::stoi(m_db.execute("SELECT COUNT(*) AS CNT FROM ?", m_tableName).data["CNT"].items[0]);
	}

	int Table::columns() const {
		return static_cast<int>(m_db.execute("SELECT * FROM ? LIMIT 1", m_tableName).data.begin()->second.items.size());
	}

	std::vector<std::string> TableWithName::getNames() const {
		SQL::TableData table = m_db.execute("SELECT name FROM ?", m_tableName);
		if (table.empty())
			return {};
		return table.data["name"].items;
	}

	bool TableWithName::has(std::string_view name) const {
		SQL::TableData table = m_db.execute("SELECT name FROM ? WHERE name = ?", m_tableName, name);
		if (table.empty())
			return false;
		return true;
	}

	void TableWithName::remove(std::string_view name) {
		m_db.execute("DELETE FROM ? WHERE name = ?", m_tableName, name);
	}
}