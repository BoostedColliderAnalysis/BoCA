/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "fastjet/PseudoJet.hh"

#include "Family.hh"
// #include "InfoRecombiner.hh"

namespace boca
{

/**
 * @brief Jet infos subclassed from Fastjet
 *
 */
class ParticleInfo: public fastjet::PseudoJet::UserInfoBase
{

public:

//     friend class InfoRecombiner;

    /**
     * @brief Constructor
     *
     */
    ParticleInfo();

    ParticleInfo(boca::Family const& family);

    boca::Family Family() const;

    void SetFamily(boca::Family const& family);

private:

    boca::Family family_;

};

}
