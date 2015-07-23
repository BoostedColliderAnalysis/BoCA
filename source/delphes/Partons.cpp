#include "delphes/Partons.hh"
#include "delphes/Delphes.hh"
#include "Predicate.hh"
#include "JetInfo.hh"
#include "Debug.hh"

namespace analysis {

namespace delphes {

Jets Partons::Particles() const
{
    return Particles(Status::stable);
}

Jets Partons::GenParticles() const
{
    return Particles(Status::generator);
}

Jets Partons::Particles(const Status min_status) const
{
    Info();
    Jets particles;
    Info(clones_arrays().ParticleSum());
    for (int particle_number : Range(clones_arrays().ParticleSum())) {
        ::delphes::GenParticle& particle = static_cast<::delphes::GenParticle&>(clones_arrays().Particle(particle_number));
        if (particle.Status < to_int(min_status))
            break;
        Detail(particle.PID);
        int mother_id = to_int(Id::empty);
        int mother_2_id = to_int(Id::empty);
        int grand_mother_id = to_int(Id::empty);
        if (particle.M1 != EmptyPosition) {
            ::delphes::GenParticle& mother = static_cast<::delphes::GenParticle&>(clones_arrays().Particle(particle.M1));
            mother_id = mother.PID;
            if (mother.M1 != EmptyPosition) {
                ::delphes::GenParticle& grand_mother = static_cast<::delphes::GenParticle&>(clones_arrays().Particle(mother.M1));
                grand_mother_id = grand_mother.PID;
            }
        }
        if (particle.M2 != EmptyPosition) {
            ::delphes::GenParticle& mother = static_cast<::delphes::GenParticle&>(clones_arrays().Particle(particle.M2));
            mother_2_id = mother.PID;
        }
        Family family(particle.PID, mother_id, mother_2_id, grand_mother_id);
        Constituent constituent(particle.P4(), family);
        fastjet::PseudoJet jet = analysis::PseudoJet(constituent.Momentum());
        jet.set_user_info(new JetInfo(constituent));
        particles.emplace_back(jet);
    }
    return particles;
}

}

}
