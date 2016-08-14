/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <sys/stat.h>
#include "boca/io/Io.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca {

bool Exists(std::string const& name) {
  INFO(name);
  struct stat buffer;
  return stat(name.c_str(), &buffer) == 0;
}

}

