#include "data_struct.hpp"
#include "iofmtguard.hpp"
#include <iomanip>

namespace nspace{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest){
    std::istream::sentry sentry(in);
    if (!sentry){
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp)){
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, CharLitIO&& dest){
    std::istream::sentry sentry(in);
    if (!sentry){
      return in;
    }
    char open = 0, value = 0, close = 0;
    in >> open >> value >> close;
    if (in){
      if (open == '\'' && close == '\''){
        dest.ref = value;
      }
      else{
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, UllHexIO&& dest){
    std::istream::sentry sentry(in);
    if (!sentry){
      return in;
    }
    char zero = 0, x = 0;
    in >> zero >> x;
    if (in){
      if (zero == '0' && (x == 'x' || x == 'X')){
        in >> std::hex >> dest.ref;
      }
      else{
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest){
    std::istream::sentry sentry(in);
    if (!sentry){
      return in;
    }
    char open = 0;
    in >> open;
    if (in){
      if (open == '"'){
        std::getline(in, dest.ref, '"');
      }
      else{
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest){
    std::istream::sentry sentry(in);
    if (!sentry){
      return in;
    }

    DataStruct input{};
    bool keys_valid[3] { false, false, false };
    std::string key_current;

    using sep = DelimiterIO;
    using chr = CharLitIO;
    using hex = UllHexIO;
    using str = StringIO;

    in >> sep{ '(' } >> sep{ ':' };

    for (std::size_t i = 0; i < 3; ++i){
      if (!in) break;

      in >> key_current;

      if (key_current == "key1"){
        in >> chr{ input.key1 } >> sep{ ':' };
        if (in) keys_valid[0] = true;
      }
      else if (key_current == "key2"){
        in >> hex{ input.key2 } >> sep{ ':' };
        if (in) keys_valid[1] = true;
      }
      else if (key_current == "key3"){
        in >> str{ input.key3 } >> sep{ ':' };
        if (in) keys_valid[2] = true;
      }
      else{
        in.setstate(std::ios::failbit);
        break;
      }
    }

    in >> sep{ ')' };

    if (in){
      if (keys_valid[0] && keys_valid[1] && keys_valid[2]){
        dest = std::move(input);
      }
      else{
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }


  bool DataStruct::operator<(const DataStruct& other) const{
    if (key1 != other.key1){
      return key1 < other.key1;
    }
    if (key2 != other.key2){
      return key2 < other.key2;
    }
    return key3.size() < other.key3.size();
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src){
    std::ostream::sentry sentry(out);
    if (!sentry){
      return out;
    }
    iofmtguard fmtguard(out);


    out << "(:key1 '" << src.key1 << "'";
    out << ":key2 0x" << std::hex << std::uppercase << src.key2;
    out << ":key3 \"" << src.key3 << "\":)";

    return out;
  }
}
