# include "delphes/Partons.hh"
# include "Predicate.hh"

namespace analysis
{

namespace delphes
{

Partons::Partons()
{
//     DebugLevel = Object::Severity::Debug;
    Print(Severity::Debug, "Constructor");
}

Jets Partons::Particles() const
{
    return Particles(Status::Stable);
}

Jets Partons::GenParticles() const
{
  return Particles(Status::Generator);
}

Jets Partons::Particles(const Status min_status) const
{
    Jets particles;
    Print(Severity::Information, "Particles", clones_arrays().ParticleSum());
    for (const int ParticleNumber : Range(clones_arrays().ParticleSum())) {
        ::delphes::GenParticle &particle = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(ParticleNumber));
        if (particle.Status < to_int(min_status)) break;
        Print(Severity::Detailed, "Particles ID", particle.PID);
        int MotherId = to_int(Id::Empty);
        int Mother2Id = to_int(Id::Empty);
        if (particle.M1 != EmptyPosition) {
            ::delphes::GenParticle &mother = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.M1));
            MotherId = mother.PID;
        }
        if (particle.M2 != EmptyPosition) {
            ::delphes::GenParticle &mother = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.M2));
            Mother2Id = mother.PID;
        }
        Print(Severity::Information, "Particles Status", "Generator");
        Family family(particle.PID, MotherId, Mother2Id);
        Constituent constituent(particle.P4(), family);
        fastjet::PseudoJet jet = analysis::PseudoJet(constituent.Momentum());
        jet.set_user_info(new JetInfo(constituent));
        particles.emplace_back(jet);
    }
    return particles;
}

}
}
