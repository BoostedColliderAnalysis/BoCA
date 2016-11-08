/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/branch/EventShapesBase.hh"
#include "boca/branch/Base.hh"
#include "boca/multivariant/OBSERVABLE_MACROS.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace branch
{

float EventShapesBase::InValue()
{
    return Base::InitialValue();
}

EventShapesBase::EventShapesBase()
{
    thrust = InValue();
    thrust_major = InValue();
    thrust_minor = InValue();
    oblateness = InValue();
    c_parameter = InValue();
    d_arameter = InValue();
    sphericity = InValue();
    aplanarity = InValue();
    planarity = InValue();
    m_max = InValue();
    m_min = InValue();
    b_max = InValue();
    b_min = InValue();
}

Observables EventShapesBase::Variables()
{
    return OBSERVABLE(thrust, "T") + OBSERVABLE(thrust_major, "T_{maj}") + OBSERVABLE(thrust_minor, "T_{min}") + OBSERVABLE(oblateness, "O") + OBSERVABLE(c_parameter, "C") + OBSERVABLE(d_arameter, "D") + OBSERVABLE(sphericity, "S") + OBSERVABLE(aplanarity, "#slash P") + OBSERVABLE(planarity, "P") + OBSERVABLE(m_max, "M_{max}") + OBSERVABLE(m_min, "M_{min}") + OBSERVABLE(b_max, "B_{max}") + OBSERVABLE(b_min, "B_{min}");
}

Observables EventShapesBase::Spectators()
{
    return {};
}

}

}
