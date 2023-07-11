#include "Database.h"

#include <iostream>
#include <iomanip>

namespace SQL {

	static TableData s_table;

	static int callback(void* NotUsed, int argc, char** argv, char** azColName) {

		for (int i = 0; i < argc; i++) {
			const char* columnName = azColName[i];
			const char* item = argv[i] ? argv[i] : "NULL";

			int& currentLength = s_table.data[columnName].maxLength;
			std::vector<std::string>& data = s_table.data[columnName].items;
			
			data.emplace_back(item);
			
			int itemLength = static_cast<int>(std::strlen(item));
			if (itemLength > currentLength)
				currentLength = itemLength;
			int columnNameLength = static_cast<int>(std::strlen(columnName));
			if (columnNameLength > currentLength)
				currentLength = columnNameLength;
		}

		return 0;
	}

	Database::Database()
		: m_db(nullptr) {
	}

	Database::Database(const std::string& path)
		: m_db(nullptr) {
		open(path);
	}

	Database::~Database() {
		close();
	}

	void Database::open(const std::string& path) {
		if (m_db)
			close();

		const int ret = sqlite3_open(path.c_str(), &m_db);

		if (ret != SQLITE_OK) {
			std::cerr << "Can't open database: " << sqlite3_errmsg(m_db) << std::endl;
			sqlite3_close(m_db);
		}
	}

	void Database::close() {
		if (m_db) {
			sqlite3_close(m_db);
			m_db = nullptr;
		}
	}

	Database::operator bool() const {
		return m_db;
	}

	TableData Database::execute(const std::string& command) const {
		if (!m_db)
			return {};

		char* errorMsg{ nullptr };
		const int ret = sqlite3_exec(m_db, command.c_str(), callback, 0, &errorMsg);

		if (ret != SQLITE_OK) {
			std::cerr << "Command:   " << command << std::endl;
			std::cerr << "SQL error: " << errorMsg << std::endl;
			sqlite3_free(errorMsg);
			return {};
		}

		const TableData table = s_table;
		s_table.clear();

		return table;
	}
}