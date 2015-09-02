/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "fastjet/PseudoJet.hh"

#include "Family.hh"

namespace boca
{

typedef std::vector<fastjet::PseudoJet> Jets;

/**
 * @brief Jet infos subclassed from Fastjet
 *
 */
class ParticleInfo: public fastjet::PseudoJet::UserInfoBase
{

public:

    friend class InfoRecombiner;

    /**
     * @brief Constructor
     *
     */
    ParticleInfo();

    ParticleInfo(boca::Family const& family);

    boca::Family Family() const;

private:

    boca::Family family_;

};

}
