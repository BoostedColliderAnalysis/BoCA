/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "boca/generic/Types.hh"
#include "boca/plotting/Orientation.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

using namespace std::string_literals;

std::string Name(Orientation orientation)
{
    auto name = ""s;
    FlagSwitch(orientation, [&](Orientation orientation_1) {
        switch (orientation_1) {
        case Orientation::none : name += " None"; break;
        case Orientation::center : name += " Center"; break;
        case Orientation::left : name += " Left"; break;
        case Orientation::right : name += " Right"; break;
        case Orientation::top : name += " Top"; break;
        case Orientation::bottom : name += " Bottom"; break;
        case Orientation::outside : name += " Outside"; break;
        default : name += std::to_string(to_int(orientation_1)); break;
        }
    });
    INFO(to_int(orientation), name);
    return name;
}

}
