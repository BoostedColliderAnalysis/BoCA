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

Jets Partons::Particles() const
{
    return Particles(Status::stable);
}

Jets Partons::GenParticles() const
{
    return Particles(Status::generator);
}

Jets Partons::Particles(Status min_status) const
{
    Info0;
    Jets jets;
    int position = 0;
    TTreeReaderArray<::delphes::GenParticle>& particles = tree_reader().Objects<::delphes::GenParticle>(Branch::particle);
    for (auto const & particle : particles) {
        if (particle.Status < to_int(min_status)) break;
        Detail(particle.PID);
        Member mother;
        Member grand_mother;
        Member great_grand_mother;
        if (particle.M1 != EmptyPosition) {
            ::delphes::GenParticle gen_mother = particles.At(particle.M1);
            mother.Set(gen_mother.PID, particle.M1);
            if (gen_mother.M1 != EmptyPosition) {
                ::delphes::GenParticle gen_grand_mother = particles.At(gen_mother.M1);
                grand_mother.Set(gen_grand_mother.PID, gen_mother.M1);
                if (gen_grand_mother.M1 != EmptyPosition) {
                    ::delphes::GenParticle& gen_great_grand_mother = particles.At(gen_grand_mother.M1);
                    great_grand_mother.Set(gen_great_grand_mother.PID, gen_grand_mother.M1);
                }
            }
        }
        Member mother_2;
        if (particle.M2 != EmptyPosition) {
            ::delphes::GenParticle& gen_mother2 = particles.At(particle.M2);
            mother_2.Set(gen_mother2.PID, particle.M2);
        }
        Family family(Member(particle.PID, position), mother, mother_2, grand_mother, great_grand_mother);
        fastjet::PseudoJet jet = boca::PseudoJet(particle.P4());
        jet.set_user_info(new ParticleInfo(family));
        jets.emplace_back(jet);
        ++position;
    }
    return jets;
}

// Member Partons::Mother(::delphes::GenParticle& particle){
//   if (particle.M1 == EmptyPosition) return {};
//   ::delphes::GenParticle mother = tree_reader().Objects<::delphes::GenParticle>(Branch::particle).At(particle.M1);
//   return {mother.PID, particle.M1};
// }

}

}

