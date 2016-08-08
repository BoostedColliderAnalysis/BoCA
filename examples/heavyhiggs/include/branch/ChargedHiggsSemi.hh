#pragma once

#include "boca/branch/Multi.hh"

namespace heavyhiggs
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief Charged Higgs semi tagger root tree structure
 *
 */
class ChargedHiggsSemi : public boca::branch::Multi
{

public:

//     float Flag;
    ChargedHiggsSemi();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
//         Flag = multiplet.Flag();
    }
//     virtual Observables Spectators();

private:

    ClassDef(ChargedHiggsSemi, 1)

};

}

}
