#ifndef SCOPE_GUARD_H
#define SCOPE_GUARD_H
#include <iostream>

class StreamGuard {
public:
    StreamGuard() = delete;
    StreamGuard(std::basic_ios<char>& stream) :
        stream_(stream),
        precision_(stream.precision()),
        flags_(stream.flags())
    {
    }
    ~StreamGuard() {
        stream_.precision(precision_);
        stream_.flags(flags_);
    }
private:
    std::basic_ios<char>& stream_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags flags_;
};

#endif /* SCOPE_GUARD_H */
