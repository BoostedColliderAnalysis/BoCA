/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/tagger/EventSingleHadronic.hh"

namespace toppartner
{

namespace tagger
{

std::string EventSingleHadronic::Name() const
{
    return "EventSingleHadronic";
}
latex::String EventSingleHadronic::LatexName() const
{
    return "T_{h}t_{l}h";
}

}

}
