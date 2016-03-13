/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "Types.hh"

#include <sys/stat.h>
#include "DEBUG.hh"

namespace boca {

bool Exists(std::string const& name) {
  INFO(name);
  struct stat buffer;
  return stat(name.c_str(), &buffer) == 0;
}

}

