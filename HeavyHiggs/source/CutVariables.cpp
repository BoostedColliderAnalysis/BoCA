/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "CutVariables.hh"
#include "Debug.hh"

namespace boca
{

void CutVariables::SetPassed(std::vector<bool> const& passed)
{
  passed_ = passed;
}

}
