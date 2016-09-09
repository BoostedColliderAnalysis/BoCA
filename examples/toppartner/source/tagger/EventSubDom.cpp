/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "toppartner/tagger/EventSubDom.hh"

namespace toppartner
{

namespace tagger
{

std::string EventSubDom::Name() const
{
    return "Event";
}

latex::String EventSubDom::LatexName() const
{
    return "T_{h} T_{l} h";
}

}

}
