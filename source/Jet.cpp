/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "Jet.hh"

namespace boca
{

JetInfo const& Jet::Info() const
{
    return jet_info_;
}

JetInfo& Jet::Info()
{
  return jet_info_;
}

}

