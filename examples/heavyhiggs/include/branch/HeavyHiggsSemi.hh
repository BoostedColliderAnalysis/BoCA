#pragma once

#include "boca/branch/Multi.hh"
#include "boca/branch/Event.hh"
#include "boca/branch/Cut.hh"

namespace heavyhiggs
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HeavyHiggsSemi : public boca::branch::Multi
{

public:

    HeavyHiggsSemi();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
    }

private:

    ClassDef(HeavyHiggsSemi, 1)

};

}

}
