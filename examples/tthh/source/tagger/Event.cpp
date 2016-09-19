/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "tthh/tagger/Event.hh"

namespace tthh
{

namespace tagger
{

std::string Event::Name() const
{
    return "Event";
}

latex::String Event::LatexName() const
{
    return "T_{h} T_{l} h_{b} h_{l}";
}

}

}
