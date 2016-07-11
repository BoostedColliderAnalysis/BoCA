/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <string>

namespace boca
{

enum class Stage
{
    trainer,
    reader
};

std::string Name(Stage stage);

}
