#include "HashMap.hpp"
#include "StringType.hpp"
#include "Object.hpp"

using namespace FM;

std::size_t FMHashMap_hash::operator()(const Object &x) const 
{
  StringType *st = x.asType<StringType>();
  ndx_t len = x.count();
  size_t hash = 5381;
  const FMChar *t = st->ro(x);
  for (ndx_t i=0;i<len;i++)
    hash = hash * 33 + t[i];
  return hash;
}
