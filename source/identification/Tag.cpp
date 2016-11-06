/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/identification/Tag.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

std::string Name(Tag tag)
{
    switch (tag) {
    case Tag::signal : return "Signal";
    case Tag::background : return "Background";
    DEFAULT("tag","");
    }
}

std::ostream& operator<<(std::ostream& stream, Tag tag)
{
  stream << Name(tag);
  return stream;
}

}
