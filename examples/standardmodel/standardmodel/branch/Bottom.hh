/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/Particle.hh"

#include "standardmodel/branch/BottomBase.hh"

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

    boca::Observables Variables();

    boca::Observables Spectators();

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
