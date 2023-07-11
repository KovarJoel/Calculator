#include "Variables.h"

#include <array>
#include <numbers>
#include <tuple>

namespace Calculator::Data {

	Variables::Variables() {}
	
	Variables::Variables(SQL::Database& database) {
		init(database);
	}

	void Variables::init(SQL::Database& database) {
		SQL::Table::init(database, "variables");
	}

	void Variables::create() {
		m_db.execute("CREATE TABLE ? (name TEXT UNIQUE NOT NULL, value REAL, reserved INTEGER DEFAULT FALSE)", m_tableName);

		constexpr std::array<std::pair<const char*, double>, 4> vars = {{
			{"pi", std::numbers::pi},
			{"e", std::numbers::e},
			{"g", 9.80665},
			{"ans", 0.0}
		}};

		for (const auto& [name, value] : vars)
			setAny(name, value);
	}

	bool Variables::set(std::string_view name, double value) {
		if (!has(name)) {
			m_db.execute("INSERT INTO ? (name, value) VALUES(?, ?)", m_tableName, name, value);
			return true;
		}

		if (isReserved(name))
			return false;

		m_db.execute("UPDATE ? SET value = ? WHERE name = ?", m_tableName, value, name);
		return true;
	}

	std::optional<double> Variables::get(std::string_view name) const {
		SQL::TableData table = m_db.execute("SELECT value FROM ? WHERE name = ?", m_tableName, name);
		if (table.empty())
			return {};
		return std::stod(table.data["value"].items[0]);
	}

	void Variables::setAny(std::string_view name, double value) {
		if (!has(name))
			m_db.execute("INSERT INTO ? (name, value, reserved) VALUES(?, ?, ?)", m_tableName, name, value, true);
		else
			m_db.execute("UPDATE ? SET value = ? WHERE name = ?", m_tableName, value, name);
	}

	bool Variables::isReserved(std::string_view name) const {
		if (!has(name))
			return false;

		return (std::stoi(m_db.execute("SELECT reserved FROM ? WHERE name = ?", m_tableName, name).data["reserved"].items[0]) == 1);
	}

	void Variables::remove(std::string_view name) {
		if (!isReserved(name))
			TableWithName::remove(name);
	}

	void Variables::removeAny(std::string_view name) {
		TableWithName::remove(name);
	}

	void Variables::removeAll() {
		m_db.execute("DELETE FROM ? WHERE reserved = ", m_tableName, false);
	}

	void Variables::removeAllAny() {
		m_db.execute("DELETE FROM ?", m_tableName);
	}
}