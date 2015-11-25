/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "CutPlet.hh"
#include "Debug.hh"

namespace boca
{

void CutPlet::SetPassed(std::vector<bool> const& passed)
{
  passed_ = passed;
}

}
