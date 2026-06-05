#include "stream_guard.hpp"

StreamGuard::StreamGuard(std::basic_ios<char>& stream)
  : stream_(stream)
  , precision_(stream.precision())
  , flags_(stream.flags())
{}

StreamGuard::~StreamGuard()
{
  stream_.precision(precision_);
  stream_.flags(flags_);
}