/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "delphes/Delphes.hh"
#include "delphes/Partons.hh"

#include "Types.hh"
#include "Debug.hh"

namespace boca
{

namespace delphes
{

namespace
{

auto Family(TTreeReaderArray<::delphes::GenParticle>& gen_particles, boca::Family& family, Relative relative, int position)
{
    if (relative == Relative::none) return family;
    if (position == Member::EmptyPosition()) return family;
    family.SetMember( {gen_particles.At(position).PID, position}, relative);
    Family(gen_particles, family, Mother(relative), gen_particles.At(position).M1);
    Family(gen_particles, family, StepMother(relative), gen_particles.At(position).M2);
    return family;
}

auto Family(TTreeReaderArray<::delphes::GenParticle>& particles, Relative relative, int position)
{
    boca::Family family;
    return Family(particles, family, relative, position);
}

}

Partons::Partons(boca::TreeReader const& tree_reader) :
    boca::Partons(tree_reader) {}

std::vector<Particle> Partons::Particles() const
{
    return Particles(Status::stable);
}

std::vector<Particle> Partons::GenParticles() const
{
    return Particles(Status::generator);
}

std::vector<Particle> Partons::Particles(Status min_status) const
{
    INFO0;
    std::vector<Particle> particles;
    auto& gen_particles = TreeReader().Objects<::delphes::GenParticle>(Branch::particle);
    auto position = 0;
    for (auto const & particle : gen_particles) {
        if (particle.Status < to_int(min_status)) break;
        particles.emplace_back(Particle(particle.P4(), Family(gen_particles, Relative::particle, position)));
        ++position;
    }
    return particles;
}

}

}
