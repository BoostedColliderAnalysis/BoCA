#pragma once

#include "boca/branch/Multi.hh"
#include "boca/branch/EventShapes.hh"

namespace toppartner
{

namespace branch
{

class VetoTopPartnerBranch : public boca::branch::Multi, public boca::branch::EventShapesBase
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
        EventShapesBase::Fill(multiplet);
    }
    virtual boca::Observables Variables();
    virtual boca::Observables Spectators();
private:
    ClassDef(VetoTopPartnerBranch, 1)
};

}

}
