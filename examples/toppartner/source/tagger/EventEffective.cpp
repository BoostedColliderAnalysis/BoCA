/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "toppartner/tagger/EventEffective.hh"

namespace toppartner
{

namespace tagger
{

std::string EventEffective::Name() const
{
    return "Event";
}

latex::String EventEffective::LatexName() const
{
    return "T_{h} T_{l} h h";
}

}

}
