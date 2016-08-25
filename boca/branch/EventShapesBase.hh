/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TObject.h"
#include "boca/Observables.hh"

namespace boca
{

namespace branch
{

/**
 * @brief %EventShapes base tree branch
 *
 */
class EventShapesBase
{
public:
    EventShapesBase();

    float thrust;
    float thrust_major;
    float thrust_minor;
    float oblateness;
    float c_parameter;
    float d_arameter;
    float sphericity;
    float aplanarity;
    float planarity;
    float m_max;
    float m_min;
    float b_max;
    float b_min;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        thrust = multiplet.EventShapes().Thrust();
        thrust_major = multiplet.EventShapes().ThrustMajor();
        thrust_minor = multiplet.EventShapes().ThrustMinor();
        oblateness = multiplet.EventShapes().Oblateness();
        c_parameter = multiplet.EventShapes().CParameter();
        d_arameter = multiplet.EventShapes().DParameter();
        sphericity = multiplet.EventShapes().Sphericity();
        aplanarity = multiplet.EventShapes().Aplanarity();
        planarity = multiplet.EventShapes().Planarity();
        m_max = multiplet.EventShapes().HemisphereMasses().MHigh2();
        m_min = multiplet.EventShapes().HemisphereMasses().MLow2();
        b_max = multiplet.EventShapes().HemisphereMasses().BMax();
        b_min = multiplet.EventShapes().HemisphereMasses().BMin();
    }
    virtual Observables Variables();
    virtual Observables Spectators();

private:
    ClassDef(EventShapesBase, 1)
    float InValue();
};

}

}
