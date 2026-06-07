#include "geometry.hpp"
#include "commands.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Error: No filename provided.\n";
		return 1;
	}

	std::ifstream file(argv[1]);
	if (!file.is_open()) {
		std::cerr << "Error: Cannot open file.\n";
		return 1;
	}

	std::vector<Polygon> polygons;
	std::string line;
	while (std::getline(file, line)) {
		if (!line.empty() && line.back() == '\r') {
			line.pop_back();
		}
		Polygon p;
		if (parsePolygon(line, p)) {
			polygons.push_back(p);
		}
	}
	file.close();

	std::string cmd;
	while (std::cin >> cmd) {
		if (cmd == "AREA" || cmd == "MAX" || cmd == "MIN" || cmd == "COUNT") {
			std::string arg;
			if (std::cin >> arg) {
				if (cmd == "AREA") cmdArea(polygons, arg);
				else if (cmd == "MAX") cmdMax(polygons, arg);
				else if (cmd == "MIN") cmdMin(polygons, arg);
				else if (cmd == "COUNT") cmdCount(polygons, arg);
			}
		} else if (cmd == "LESSAREA" || cmd == "MAXSEQ") {
			std::string remainder;
			std::getline(std::cin, remainder);
			if (!remainder.empty() && remainder.front() == ' ') {
				remainder.erase(0, 1);
			}
			Polygon p;
			if (parsePolygon(remainder, p)) {
				if (cmd == "LESSAREA") cmdLessArea(polygons, p);
				else cmdMaxSeq(polygons, p);
			} else {
				std::cout << "<INVALID COMMAND>\n";
			}
		} else {
			std::cout << "<INVALID COMMAND>\n";
			std::string dummy;
			std::getline(std::cin, dummy);
		}
	}

	return 0;
}
