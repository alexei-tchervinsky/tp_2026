#include <vector>
#include <iostream>
#include <functional>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <numeric>
#include <limits>
#include <cmath>
#include <cctype>

namespace plg{
    struct Point{
        int x, y;
    };
    bool operator==(const Point& lhs, const Point& rhs){
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    std::istream& operator>>(std::istream& is, Point& pt){
            char ch1 = 0, ch2 = 0, ch3 = 0;
            int temp_x = 0, temp_y = 0;
            if(is >> ch1 >> temp_x >> ch2 >> temp_y >> ch3){
                if (ch1 == '(' && ch2 == ';' && ch3 == ')'){
                    pt.x = temp_x;
                    pt.y = temp_y;
                }
                else{
                    std::cerr << "Error: wrong input" << '\n';
                    is.setstate(std::ios::failbit);
                }
            }
            return is;
        }

    struct Polygon{
        std::vector< Point > points;
    };
    bool operator==(const Polygon& lhs, const Polygon& rhs){
        return lhs.points == rhs.points;
    }
    std::istream& operator>>(std::istream& is, Polygon& pn){
        int num_vertexes;
        if (!(is >> num_vertexes)) {
            is.setstate(std::ios::failbit);
            return is;
        }
        if (num_vertexes < 3) {
            is.setstate(std::ios::failbit);
            return is;
        }
        pn.points.clear();
        pn.points.resize(num_vertexes);
        for (int i = 0; i < num_vertexes; ++i) {
            if (!(is >> pn.points[i])) {
                is.setstate(std::ios::failbit);
                return is;
            }
        }
        int next = is.peek();
        while (next != EOF && std::isspace(next) && next != '\n' && next != '\r') {
            is.get();
            next = is.peek();
        }
        if (next != EOF && next != '\n' && next != '\r') {
            is.setstate(std::ios::failbit);
            return is;
        }
        return is;
    }
    struct AreaAccumulator{
        const std::vector<Point>& pts;
        AreaAccumulator(const std::vector<Point>& points) : pts(points){}
        double operator()(double current_sum, size_t i) const {
            size_t next_i = (i + 1) % pts.size();
            return current_sum + (pts[i].x * pts[next_i].y - pts[i].y * pts[next_i].x);
        }
    };
    double getArea(const Polygon& pn){
        const std::vector<Point>& pts = pn.points;
        if (pts.size() < 3){
            return 0.0;
        }
        std::vector<size_t> indeces(pts.size());
        std::iota(indeces.begin(), indeces.end(), 0);
        double sum = std::accumulate(indeces.begin(), indeces.end(), 0.0, AreaAccumulator(pts));
        return std::abs(sum) / 2.0;
    }
    struct AreaEvenAccumulator{
        bool target_even;
        AreaEvenAccumulator(bool even) : target_even(even) {}
        double operator()(double current_sum, const Polygon& pn) const{
            bool is_even = (pn.points.size() % 2 == 0);
            if (is_even == target_even){
                return current_sum + getArea(pn);
            }
            return current_sum;
        }
    };
    struct AreaVertexAccumulator{
        size_t target_vertexes;
        AreaVertexAccumulator(size_t num) : target_vertexes(num){}
        double operator()(double current_sum, const Polygon& pn) const{
            if(pn.points.size() == target_vertexes){
                return current_sum + getArea(pn);
            }
            return current_sum;
        }
    };
    struct AreaTotalAccumulator{
        double operator()(double current_sum, const Polygon& pn) const{
            return current_sum + getArea(pn);
        }
    };
    void area(const std::vector<Polygon>& database, std::istream& is, std::ostream& os){
        std::string argument;
        if(!(is >> argument)){
            throw std::logic_error("Mising command");
        }
        os << std::fixed << std::setprecision(1);
        if (argument == "EVEN"){
            double result =  std::accumulate(database.begin(), database.end(), 0.0, AreaEvenAccumulator(true));
            os << result << "\n";
        }
        else if (argument == "ODD"){
            double result =  std::accumulate(database.begin(), database.end(), 0.0, AreaEvenAccumulator(false));
            os << result << "\n";
        }
        else if (argument == "MEAN"){
            if (database.empty()){
                throw std::logic_error("Database is empty");
            }
            double total_area = std::accumulate(database.begin(), database.end(), 0.0, AreaTotalAccumulator());
            os << total_area/database.size() << "\n";
        }
        else{
            try{
                int num = std::stoi(argument);
                if (num < 3){
                    throw std::logic_error("Invalid vertex number");
                }
                double result = std::accumulate(database.begin(), database.end(), 0.0, AreaVertexAccumulator(num));
                os << result << "\n";
            }
            catch (...){
                throw std::logic_error("Invalid argument");
            }
        }
    }
    struct AreaComparator{
        bool operator()(const Polygon& a, const Polygon& b) const{
            return getArea(a) < getArea(b);
        }
    };
    struct  VertexComparator{
        bool operator()(const Polygon& a, const Polygon& b) const{
            return a.points.size() < b.points.size();
        }
    };
    void max(const std::vector<Polygon>& database, std::istream& is, std::ostream& os){
        if (database.empty()){
            throw std::logic_error("Database in empty");
        }
        std::string argument;
        if(!(is >> argument)){
            throw std::logic_error("Mising command");
        }
        if (argument == "AREA"){
            std::vector<Polygon>::const_iterator it =  std::max_element(database.begin(), database.end(), AreaComparator());
            os << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
        }
        else if (argument == "VERTEXES"){
            std::vector<Polygon>::const_iterator it =  std::max_element(database.begin(), database.end(), VertexComparator());
            os << it->points.size() << "\n";;
        }
        else{
            throw std::logic_error("Invalid argument");
        }
    }
     void min(const std::vector<Polygon>& database, std::istream& is, std::ostream& os){
        if (database.empty()){
            throw std::logic_error("Database in empty");
        }
        std::string argument;
        if(!(is >> argument)){
            throw std::logic_error("Mising command");
        }
        if (argument == "AREA"){
            std::vector<Polygon>::const_iterator it =  std::min_element(database.begin(), database.end(), AreaComparator());
            os << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
        }
        else if (argument == "VERTEXES"){
            std::vector<Polygon>::const_iterator it =  std::min_element(database.begin(), database.end(), VertexComparator());
            os << it->points.size() << "\n";;
        }
        else{
            throw std::logic_error("Invalid argument");
        }
    }
    struct CountEven{
        bool target_even;
        CountEven(bool even) : target_even(even){}
        bool operator()(const Polygon& pn){
            return (pn.points.size() % 2 == 0) == target_even;
        }
    };
    struct CountVertex{
        size_t target_vertexes;
        CountVertex(size_t num) : target_vertexes(num){}
        bool operator()(const Polygon& pn) const{
            return pn.points.size() == target_vertexes;
        }
    };
    void count(const std::vector<Polygon>& database, std::istream& is, std::ostream& os){
        std::string argument;
        if(!(is >> argument)){
            throw std::logic_error("Mising command");
        }
        if (argument == "EVEN"){
            std::size_t result =  std::count_if(database.begin(), database.end(), CountEven(true));
            os << result << "\n";
        }
        else if (argument == "ODD"){
            std::size_t result =  std::count_if(database.begin(), database.end(), CountEven(false));
            os << result << "\n";
        }
        else {
             try{
                int num = std::stoi(argument);
                if (num < 3){
                    throw std::logic_error("Invalid vertex number");
                }
                std::size_t result = std::count_if(database.begin(), database.end(), CountVertex(num));
                os << result << "\n";
            }
            catch (...){
                throw std::logic_error("Invalid argument");
            }
        }
    }
    struct EchoAccumulator{
        const Polygon& target;
        EchoAccumulator(const Polygon& tgt) : target(tgt) {}
        std::vector<Polygon> operator()(std::vector<Polygon> vec, const Polygon& pn) const{
            vec.push_back(pn);
            if (pn == target){
                vec.push_back(pn);
            }
            return vec;
        }
    };
    void echo(std::vector<Polygon>& database, std::istream& is, std::ostream& os){
        Polygon target;
        if(!(is >> target)){
            throw std::logic_error("Mising command");
        }
        size_t add_figures= std::count(database.begin(), database.end(), target);
        std::vector<Polygon> new_vector;
        new_vector.reserve(database.size() + add_figures);
        std::vector<Polygon> new_database = std::accumulate(database.begin(), database.end(),
        new_vector, EchoAccumulator(target));
        database = std::move(new_database);
        os << add_figures << "\n";
    }
    struct MaxSeqState{
        size_t current_streak;
        size_t max_streak;
    };
    struct MaxSeqProcessor {
        const Polygon& target;
        MaxSeqProcessor(const Polygon& tgt) : target(tgt) {}

        MaxSeqState operator()(MaxSeqState state, const Polygon& current) const{
            if (current == target){
                state.current_streak++;
                if (state.current_streak > state.max_streak){
                    state.max_streak = state.current_streak;
                }
            }
            else{
                state.current_streak = 0;
            }
            return state;
        }
    };
    void maxseq(const std::vector<Polygon>& database, std::istream& is, std::ostream& os){
        Polygon target;
        if (!(is >> target)){
             throw std::logic_error("Invalid target polygon");
        }
        MaxSeqState final_state = std::accumulate(
            database.begin(), database.end(),
            MaxSeqState{}, MaxSeqProcessor(target)
        );
        os << final_state.max_streak << "\n";
    }
}

int main(int argc, char* argv[]){
    using plg::Polygon;
    if (argc < 2){
        std::cerr << "Error: filename is not specified " << '\n';
        return 1;
    }
    std::fstream file(argv[1]);
    if(!file.is_open()){
        std::cerr << "Error: filename is not specified\n";
        return 1;
    }
   std::vector<Polygon> database;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream iss(line);
        plg::Polygon pn;
        try {
            if (iss >> pn) {
                database.push_back(pn);
            }
        }
        catch (const std::logic_error&) {
            continue;
        }
    }
    file.close();
        std::map<std::string, std::function<void()>> cmds;
        cmds["AREA"] = std::bind(plg::area, std::cref(database), std::ref(std::cin), std::ref(std::cout));
        cmds["MAX"] = std::bind(plg::max, std::cref(database), std::ref(std::cin), std::ref(std::cout));
        cmds["MIN"] = std::bind(plg::min, std::cref(database), std::ref(std::cin), std::ref(std::cout));
        cmds["COUNT"] = std::bind(plg::count, std::cref(database), std::ref(std::cin), std::ref(std::cout));
        cmds["ECHO"] = std::bind(plg::echo, std::ref(database), std::ref(std::cin), std::ref(std::cout));
        cmds["MAXSEQ"] = std::bind(plg::maxseq, std::cref(database), std::ref(std::cin), std::ref(std::cout));
    std::string command;
    while(!(std::cin >> command).eof()){
        try{
            cmds.at(command)();
        }
        catch(...){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "<INVALID COMMAND>\n";
        }
    }
        return 0;
}
