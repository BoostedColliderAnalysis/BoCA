/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/branch/BottomBase.hh"
#include "boca/branch/Base.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace boca
{

namespace standardmodel
{

namespace branch
{

BottomBase::BottomBase()
{
    vertex_mass = InValue();
    max_displacement = InValue();
    mean_displacement = InValue();
    sum_displacement = InValue();
    multiplicity = static_cast<int>(InValue());
    radius = InValue();
    spread = InValue();
    vertex_radius = InValue();
    vertex_spread = InValue();
    energy_fraction = InValue();
    energy_ratio = InValue();
    momentum_ratio = InValue();
}

Observables BottomBase::Variables()
{
    return OBSERVABLE(vertex_mass, latex::String("m_{V}") + " [GeV]") +
    OBSERVABLE(max_displacement, "log(" + latex::String("\\Delta d") + "_{max} / mm)") +
    OBSERVABLE(mean_displacement, "log(" + latex::String("\\Delta d") + "_{mean} / mm)") +
    OBSERVABLE(sum_displacement, "log(" + latex::String("\\Delta d") + "_{sum} / mm)") +
    OBSERVABLE(multiplicity, latex::String("n_{V}")) +
    OBSERVABLE(radius, latex::String("r")) +
    OBSERVABLE(spread, latex::String("s")) +
    OBSERVABLE(vertex_radius, latex::String("r_{V}")) +
    OBSERVABLE(vertex_spread, latex::String("s_{V}")) +
    OBSERVABLE(energy_fraction, latex::String("f_{E}"));
}

Observables BottomBase::Spectators()
{
  return OBSERVABLE(energy_ratio, latex::String("r_{E}")) + OBSERVABLE(momentum_ratio, latex::String("r_{p}"));
}

float BottomBase::InValue()
{
    return boca::branch::Base::InitialValue();
}

}

}

}
