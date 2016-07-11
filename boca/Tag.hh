/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <string>

namespace boca {

enum class Tag {
    background = 0,
    signal = 1
};

std::string Name(Tag tag);

}

