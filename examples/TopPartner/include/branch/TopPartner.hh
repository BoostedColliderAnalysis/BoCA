#pragma once

#include "boca/branch/Multi.hh"

namespace toppartner
{

namespace branch
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class TopPartnerBranch : public ::boca::branch::Multi
{
public:
    TopPartnerBranch();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
    }
private:
    ClassDef(TopPartnerBranch, 1)
};

}

}
