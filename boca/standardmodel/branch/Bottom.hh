/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/standardmodel/branch/BottomBase.hh"
#include "boca/branch/Particle.hh"

namespace boca
{

namespace standardmodel
{

/**
* @brief Tree branches
*
*/
namespace branch
{

/**
 *
 * @brief %Bottom tagger tree branch
 *
 */
class Bottom : public boca::branch::Particle, public BottomBase
{

public:

    Observables Variables();

    Observables Spectators();

    template<typename Multiplet>
    void Fill(Multiplet const &multiplet)
    {
        Particle::Fill(multiplet);
        BottomBase::Fill(multiplet);
    }

private:

    ClassDef(Bottom, 1)

};

}

}

}
