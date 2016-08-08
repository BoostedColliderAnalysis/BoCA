#pragma once

#include "boca/branch/Multi.hh"

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
