/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "delphes/Delphes.hh"
#include "delphes/Partons.hh"

#include "Types.hh"
#include "ParticleInfo.hh"
#include "Debug.hh"

namespace boca
{

namespace delphes
{

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
    int position = 0;
    auto & gen_particles = TreeReader().Objects<::delphes::GenParticle>(Branch::particle);
    for (auto const & gen_particle : gen_particles) {
        if (gen_particle.Status < to_int(min_status)) break;
        DETAIL(gen_particle.PID);
        Member mother;
        Member grand_mother;
        Member great_grand_mother;
        if (gen_particle.M1 != Member::EmptyPosition()) {
            auto gen_mother = gen_particles.At(gen_particle.M1);
            mother.Set(gen_mother.PID, gen_particle.M1);
            if (gen_mother.M1 != Member::EmptyPosition()) {
                auto & gen_grand_mother = gen_particles.At(gen_mother.M1);
                grand_mother.Set(gen_grand_mother.PID, gen_mother.M1);
                if (gen_grand_mother.M1 != Member::EmptyPosition()) {
                    auto & gen_great_grand_mother = gen_particles.At(gen_grand_mother.M1);
                    great_grand_mother.Set(gen_great_grand_mother.PID, gen_grand_mother.M1);
                }
            }
        }
        Member mother_2;
        if (gen_particle.M2 != Member::EmptyPosition()) {
            auto & gen_mother2 = gen_particles.At(gen_particle.M2);
            mother_2.Set(gen_mother2.PID, gen_particle.M2);
        }
        Member particle(gen_particle.PID, position);
        Family family(particle, mother, mother_2, grand_mother, great_grand_mother);
        particles.emplace_back(Particle(gen_particle.P4(), family));
        ++position;
    }
    return particles;
}

// Member GrandMother(TTreeReaderArray<::delphes::GenParticle>& gen_particles, ::delphes::GenParticle gen_mother){
//   if (gen_mother.M1 != Member::EmptyPosition()) {
//     ::delphes::GenParticle gen_grand_mother = gen_particles.At(gen_mother.M1);
//     grand_mother.Set(gen_grand_mother.PID, gen_mother.M1);
//     GreatGrandMother(gen_particles, gen_grand_mother);
//   }
//
// }
//
// Member GreatGrandMother(TTreeReaderArray<::delphes::GenParticle>& gen_particles, ::delphes::GenParticle gen_grand_mother)
// {
//     Member great_grand_mother;
//     if (gen_grand_mother.M1 != Member::EmptyPosition()) {
//         ::delphes::GenParticle& gen_great_grand_mother = gen_particles.At(gen_grand_mother.M1);
//         great_grand_mother.Set(gen_great_grand_mother.PID, gen_grand_mother.M1);
//     }
//     return great_grand_mother;
// }

// Member Partons::Mother(::delphes::GenParticle& particle){
//   if (particle.M1 == Member::EmptyPosition()) return {};
//   ::delphes::GenParticle mother = TreeReader().Objects<::delphes::GenParticle>(Branch::particle).At(particle.M1);
//   return {mother.PID, particle.M1};
// }

}

}


