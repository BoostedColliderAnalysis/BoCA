/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <string>

namespace boca
{

enum class Source
{
    delphes,
    pgs,
    parton,
    tagger
};

std::string Name(Source source);

}
