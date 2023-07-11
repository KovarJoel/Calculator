#include "TableData.h"

#include <iomanip>
#include <iostream>

namespace SQL {

	bool TableData::empty() const {
		return data.empty();
	}

	void TableData::clear() {
		data.clear();
	}

	int TableData::columns() const {
		return static_cast<int>(data.size());
	}

	int TableData::rows() const {
		if (empty())
			return 0;

		return static_cast<int>(data.begin()->second.items.size());
	}

	void TableData::print() const {

		if (empty())
			return;

		printSeperator();
		printHeader();
		printSeperator();

		printBody();

		printSeperator();
	}

	void TableData::printHeader() const {
		for (const auto& [headerName, column] : data)
			std::cout << "| " << std::setw(column.maxLength) << headerName << ' ';
		std::cout << '|' << std::endl;
	}
	
	void TableData::printBody() const {
		for (int i = 0, rows = this->rows(); i < rows; ++i) {
			for (const auto& [headerName, column] : data)
				std::cout << "| " << std::setw(column.maxLength) << column.items[i] << ' ';
			std::cout << "|\n";
		}
	}
	
	void TableData::printSeperator() const {
		std::cout << std::setfill('-') << std::left;
		for (const auto& [headerName, column] : data)
			std::cout << std::setw(column.maxLength + paddingWidth) << '+';
		std::cout << std::setfill(' ');
		std::cout << '+' << std::endl;
	}
}