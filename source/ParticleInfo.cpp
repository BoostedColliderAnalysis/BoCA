/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "ParticleInfo.hh"

#include "Debug.hh"

namespace boca {

ParticleInfo::ParticleInfo()
{
    Debug();
}

ParticleInfo::ParticleInfo(boca::Family const& family)
{
    family_ = family;
}

boca::Family ParticleInfo::Family() const
{
    return family_;
}

}
