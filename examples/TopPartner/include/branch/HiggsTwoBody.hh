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
class HiggsTwoBody : public boca::branch::Multi
{
public:
    HiggsTwoBody();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
    }
private:
    ClassDef(HiggsTwoBody, 1)
};

// class ThreeBody : public Multi
// {
// public:
//     template<typename Multiplet>
//     void Fill(Multiplet const& multiplet) {
//         Multi::Fill(multiplet);
//     }
// private:
//     ClassDef(ThreeBody, 1)
// };

}

}
