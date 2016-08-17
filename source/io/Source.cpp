/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/generic/Types.hh"
#include "boca/io/Souce.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

std::string Name(Source source)
{
    switch (source) {
    case Source::delphes : return "Delphes";
    case Source::snowmass : return "Snowmass";
    case Source::pgs : return "PGS";
    case Source::parton : return "Parton";
    case Source::tagger : return "Tagger";
        DEFAULT(to_int(source), "");
    }
}

}
