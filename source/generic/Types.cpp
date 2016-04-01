/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <sys/stat.h>
#include "generic/Types.hh"
#include "generic/DEBUG.hh"

namespace boca {

bool Exists(std::string const& name) {
  INFO(name);
  struct stat buffer;
  return stat(name.c_str(), &buffer) == 0;
}

}

