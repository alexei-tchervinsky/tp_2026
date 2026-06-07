#include "commands.hpp"
#include <numeric>
#include <algorithm>
#include <iostream>
#include <iomanip>

void cmdArea(const std::vector<Polygon>& polygons, const std::string& arg) {
	if (arg == "MEAN" && polygons.empty()) {
		std::cout << "<INVALID COMMAND>\n";
		return;
	}
	if (arg == "EVEN") {
		double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
			[](double acc, const Polygon& p) {
				return acc + (p.points.size() % 2 == 0 ? getArea(p) : 0.0);
			});
		std::cout << std::fixed << std::setprecision(1) << sum << "\n";
	} else if (arg == "ODD") {
		double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
			[](double acc, const Polygon& p) {
				return acc + (p.points.size() % 2 != 0 ? getArea(p) : 0.0);
			});
		std::cout << std::fixed << std::setprecision(1) << sum << "\n";
	} else if (arg == "MEAN") {
		double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
			[](double acc, const Polygon& p) { return acc + getArea(p); });
		std::cout << std::fixed << std::setprecision(1) << (sum / polygons.size()) << "\n";
	} else {
		try {
			size_t num = std::stoull(arg);
			double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
				[num](double acc, const Polygon& p) {
					return acc + (p.points.size() == num ? getArea(p) : 0.0);
				});
			std::cout << std::fixed << std::setprecision(1) << sum << "\n";
		} catch (...) {
			std::cout << "<INVALID COMMAND>\n";
		}
	}
}

void cmdMax(const std::vector<Polygon>& polygons, const std::string& arg) {
	if (polygons.empty()) {
		std::cout << "<INVALID COMMAND>\n";
		return;
	}
	if (arg == "AREA") {
		auto it = std::max_element(polygons.begin(), polygons.end(),
			[](const Polygon& a, const Polygon& b) {
				return getArea(a) < getArea(b);
			});
		std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
	} else if (arg == "VERTEXES") {
		auto it = std::max_element(polygons.begin(), polygons.end(),
			[](const Polygon& a, const Polygon& b) {
				return a.points.size() < b.points.size();
			});
		std::cout << it->points.size() << "\n";
	} else {
		std::cout << "<INVALID COMMAND>\n";
	}
}

void cmdMin(const std::vector<Polygon>& polygons, const std::string& arg) {
	if (polygons.empty()) {
		std::cout << "<INVALID COMMAND>\n";
		return;
	}
	if (arg == "AREA") {
		auto it = std::min_element(polygons.begin(), polygons.end(),
			[](const Polygon& a, const Polygon& b) {
				return getArea(a) < getArea(b);
			});
		std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
	} else if (arg == "VERTEXES") {
		auto it = std::min_element(polygons.begin(), polygons.end(),
			[](const Polygon& a, const Polygon& b) {
				return a.points.size() < b.points.size();
			});
		std::cout << it->points.size() << "\n";
	} else {
		std::cout << "<INVALID COMMAND>\n";
	}
}

void cmdCount(const std::vector<Polygon>& polygons, const std::string& arg) {
	if (arg == "EVEN") {
		std::cout << std::count_if(polygons.begin(), polygons.end(),
			[](const Polygon& p) { return p.points.size() % 2 == 0; }) << "\n";
	} else if (arg == "ODD") {
		std::cout << std::count_if(polygons.begin(), polygons.end(),
			[](const Polygon& p) { return p.points.size() % 2 != 0; }) << "\n";
	} else {
		try {
			size_t num = std::stoull(arg);
			std::cout << std::count_if(polygons.begin(), polygons.end(),
				[num](const Polygon& p) { return p.points.size() == num; }) << "\n";
		} catch (...) {
			std::cout << "<INVALID COMMAND>\n";
		}
	}
}

void cmdLessArea(const std::vector<Polygon>& polygons, const Polygon& p) {
	double targetArea = getArea(p);
	size_t count = std::count_if(polygons.begin(), polygons.end(),
		[targetArea](const Polygon& poly) { return getArea(poly) < targetArea; });
	std::cout << count << "\n";
}

void cmdMaxSeq(const std::vector<Polygon>& polygons, const Polygon& target) {
	auto result = std::accumulate(polygons.begin(), polygons.end(), std::make_pair(0, 0),
		[&target](std::pair<int, int> state, const Polygon& p) {
			if (p == target) {
				state.first++;
				state.second = std::max(state.second, state.first);
			} else {
				state.first = 0;
			}
			return state;
		});
	std::cout << result.second << "\n";
}
