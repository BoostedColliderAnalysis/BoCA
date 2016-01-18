/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <mutex>

namespace boca
{

class ReaderBase
{

public:

static  std::mutex mutex_;

};

}
