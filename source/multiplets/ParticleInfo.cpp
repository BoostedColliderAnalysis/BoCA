/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "multiplets/ParticleInfo.hh"

#include "generic/DEBUG.hh"

namespace boca {

ParticleInfo::ParticleInfo()
{
    DEBUG0;
}

ParticleInfo::ParticleInfo(boca::Family const& family)
{
    family_ = family;
}

boca::Family ParticleInfo::Family() const
{
    return family_;
}

void ParticleInfo::SetFamily(boca::Family const& family)
{
    family_ = family;
}

}
