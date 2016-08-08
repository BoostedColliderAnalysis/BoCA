#pragma once

#include "boca/branch/ThreeBody.hh"
#include "boca/branch/TwoBody.hh"
#include "boca/branch/Multi.hh"
#include "boca/branch/Event.hh"

namespace higgscpv
{

namespace branch
{

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class TopLeptonicTwoBody : public boca::branch::Multi
{
public:
    TopLeptonicTwoBody();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
    }
private:
    ClassDef(TopLeptonicTwoBody, 1)
};

}

}
