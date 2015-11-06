/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "delphes/Delphes.hh"
#include "delphes/Partons.hh"

#include "Types.hh"
#include "ParticleInfo.hh"
#include "Debug.hh"

namespace boca {

namespace delphes {

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
//     Info(tree_reader().ParticleSum());
//     std::vector<::delphes::GenParticle> particles =
    TTreeReaderArray<::delphes::GenParticle> & particles =
    tree_reader().Objects<::delphes::GenParticle>(Branch::particle);
    for (auto const& particle : particles) {
//         ::delphes::GenParticle& particle = tree_reader().Particle(particle_number));
        if (particle.Status < to_int(min_status)) break;
        Detail(particle.PID);
        int mother_id = to_int(Id::empty);
        int grand_mother_id = to_int(Id::empty);
        int grand_grand_mother_id = to_int(Id::empty);
        if (particle.M1 != EmptyPosition) {
          ::delphes::GenParticle mother = particles.At(particle.M1);
            mother_id = mother.PID;
            if (mother.M1 != EmptyPosition) {
              ::delphes::GenParticle grand_mother = particles.At(mother.M1);
                grand_mother_id = grand_mother.PID;
                if (grand_mother.M1 != EmptyPosition) {
                  ::delphes::GenParticle& grand_grand_mother = particles.At(grand_mother.M1);
                  grand_grand_mother_id = grand_grand_mother.PID;
                }
            }
        }
        int mother_2_id = to_int(Id::empty);
        if (particle.M2 != EmptyPosition) {
          ::delphes::GenParticle& mother2 = particles.At(particle.M2);
            mother_2_id = mother2.PID;
//             Error(particle_number,particle.PID,particle.M2,mother2.PID);
        }
//              Error(particle.PID,mother_id,mother_2_id);
        Family family(particle.PID, mother_id, mother_2_id, grand_mother_id, grand_grand_mother_id);
        fastjet::PseudoJet jet = boca::PseudoJet(particle.P4());
        jet.set_user_info(new ParticleInfo(family));
        jets.emplace_back(jet);
//         if(std::abs(particle.PID) == 25) {
//           Error(particle_number, particle.M1, particle.M2);
//           Error(particle.PID, mother_id, mother_2_id, grand_mother_id);
//         }
    }
    return jets;
}

// int Partons::MotherId(::delphes::GenParticle& particle){
//   if (particle.M1 == EmptyPosition) return to_int(Id::empty);
//   ::delphes::GenParticle grand_grand_mother = tree_reader().Objects<::delphes::GenParticle>(Branch::particle).at(particle.M1);
//   return grand_grand_mother.PID;
// }

}

}

