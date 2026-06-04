#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

namespace golovach {
  struct DataStruct {
    double key1;
    char key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct tmp;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    char c = 0;
    in >> c;
    if (c != '(') { in.setstate(std::ios::failbit); return in; }
    in >> c;
    if (c != ':') { in.setstate(std::ios::failbit); return in; }

    for (int i = 0; i < 3; i++) {
      std::string key;
      in >> key;
      if (!in) return in;

      if (key == "key1") {
        in >> tmp.key1;
        char suffix = 0;
        in >> suffix;
        if (suffix != ':') in.putback(suffix);
        hasKey1 = true;
      } else if (key == "key2") {
        in >> c;
        in.get(tmp.key2);
        in >> c;
        in >> c;
        hasKey2 = true;
      } else if (key == "key3") {
        in >> c;
        std::getline(in, tmp.key3, '"');
        in >> c;
        hasKey3 = true;
      } else {
        in.setstate(std::ios::failbit);
        return in;
      }
    }

    in >> c;
    if (!in) return in;

    if (hasKey1 && hasKey2 && hasKey3) {
      dest = tmp;
    } else {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    out << "(:key1 " << std::scientific << src.key1;
    out << ":key2 '" << src.key2 << "'";
    out << ":key3 \"" << src.key3 << "\"";
    out << ":)";
    return out;
  }

  bool compare(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
  }
}

int main() {
  using namespace golovach;

  std::vector<DataStruct> data;

  std::copy(
    std::istream_iterator<DataStruct>(std::cin),
    std::istream_iterator<DataStruct>(),
    std::back_inserter(data)
  );

  std::sort(data.begin(), data.end(), compare);

  std::copy(
    data.begin(),
    data.end(),
    std::ostream_iterator<DataStruct>(std::cout, "\n")
  );

  return 0;
}
