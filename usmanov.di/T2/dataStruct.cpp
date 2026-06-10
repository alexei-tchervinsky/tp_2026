#include "dataStruct.h"
#include "IOFormat.h"
#include <iomanip>

bool DataStructComparator::operator()(const DataStruct& left, const DataStruct& right) const
{
  if (left.key1 != right.key1)
  {
    return left.key1 < right.key1;
  }

  if (left.key2 != right.key2)
  {
    return left.key2 < right.key2;
  }

  return left.key3.length() < right.key3.length();
}

std::istream& operator>>(std::istream& in, DataStruct& dataStruct)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  DataStruct temp;
  bool hasKey1 = false;
  bool hasKey2 = false;
  bool hasKey3 = false;

  in >> DelimeterIO{ '(' };
  if (!in)
  {
    return in;
  }

  while (!(hasKey1 && hasKey2 && hasKey3))
  {
    in >> DelimeterIO{ ':' };
    if (!in)
    {
      break;
    }

    std::string label;
    in >> label;
    if (!in)
    {
      break;
    }

    if (label == "key1" && !hasKey1)
    {
      in >> DblLitIO{ temp.key1 };
      if (!in)
      {
        break;
      }
      hasKey1 = true;
    }
    else if (label == "key2" && !hasKey2)
    {
      in >> SllLitIO{ temp.key2 };
      if (!in)
      {
        break;
      }
      hasKey2 = true;
    }
    else if (label == "key3" && !hasKey3)
    {
      in >> StringIO{ temp.key3 };
      if (!in)
      {
        break;
      }
      hasKey3 = true;
    }
    else
    {
      in.setstate(std::ios::failbit);
      break;
    }
  }

  in >> DelimeterIO{ ':' };
  if (!in)
  {
    return in;
  }

  in >> DelimeterIO{ ')' };
  if (!in)
  {
    return in;
  }

  if (hasKey1 && hasKey2 && hasKey3)
  {
    dataStruct = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  iofguard guard(out);

  out << "(:";
  out << "key1 " << std::fixed << std::setprecision(1) << dataStruct.key1 << "d:";
  out << "key2 " << dataStruct.key2 << "ll:";
  out << "key3 \"" << dataStruct.key3 << "\":";
  out << ")";

  return out;
}
