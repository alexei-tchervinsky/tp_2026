#include "DataStruct.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <cmath>


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
    std::istream& operator>>(std::istream& in, CharIO&& dest){
        std::istream::sentry sentry(in);
        if (!sentry){
            return in;
        }
        in >> DelimiterIO{'\''} >> dest.ref >> DelimiterIO{'\''};
        return in;
    }
    std::istream& operator>>(std::istream& in, ComplexIO&& dest){
        std::istream::sentry sentry(in);
        if (!sentry){
            return in;
        }
        double real = 0.0;
        double imag = 0.0;
        in >> DelimiterIO{'#'} >> DelimiterIO{'c'} >> DelimiterIO{'('} >> real >> imag >> DelimiterIO{')'};
        if (in){
            dest.ref = {real, imag};
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, StringIO&& dest){
        std::istream::sentry sentry(in);
        if (!sentry){
            return in;
        }
        return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
    }
    std::istream& operator>>(std::istream& in, DataStruct& dest){
         std::istream::sentry sentry(in);
        if (!sentry){
            return in;
        }
        DataStruct input;
        bool keys_valid[3] = {false, false, false};
        std::size_t keys_valid_size = sizeof(keys_valid) / sizeof(keys_valid[0]);
        std::size_t key_valid_last = keys_valid_size - 1;
        std::string key_current;
        {
            using sep = DelimiterIO;
            using chr = CharIO;
            using cmp = ComplexIO;
            using str = StringIO;
            in >> sep{'('};
            for (size_t i = 0; i < keys_valid_size; ++i){
                in >> sep{':'} >> key_current;
                if (in && key_current == "key1"){
                    in >> chr{input.key1};
                    if (in){
                        keys_valid[0] = true;
                    }
                }
                else if (in && key_current == "key2"){
                    in >> cmp{input.key2};
                    if (in){
                        keys_valid[1] = true;
                    }
                }
                else if (in && key_current == "key3"){
                    in >> str{input.key3};
                    if (in){
                        keys_valid[2] = true;
                    }
                }
            }
            in >> sep{':'} >> sep{')'};
        }
        if (in){
            if (keys_valid[0] == true && keys_valid[1] == true && keys_valid[2] == true){
                dest = std::move(input);
            }
            else{
                    in.setstate(std::ios::failbit);
            }
        }
      return in;
    }
    std::ostream& operator<<(std::ostream& out, const DataStruct& src){
        std::ostream::sentry sentry(out);
        if (!sentry){
            return out;
        }
        iofmtguard guard(out);
        out << "(:key1 '" << src.key1 << "'";
        out << ":key2 #c(" << std::fixed << std::setprecision(1) << src.key2.real() << " " <<
        src.key2.imag() << ")";
        out << ":key3 \"" << src.key3 << "\":)";
        return out;
    }

    bool DataStruct::operator < (const DataStruct & other) const {
        if (key1 != other.key1){
            return key1 < other.key1;
        }
        double abs1 = std::abs(key2);
        double abs2 = std::abs(other.key2);
        if (abs1 != abs2){
            return abs1 < abs2;
        }
        return key3.length() < other.key3.length();
    }
}
