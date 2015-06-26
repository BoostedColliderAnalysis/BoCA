# include "delphes/Partons.hh"
# include "Predicate.hh"

namespace analysis
{

namespace delphes
{

Partons::Partons()
{
//     DebugLevel = Severity::debug;
    Print(Severity::debug, "Constructor");
}

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
    Jets particles;
    Print(Severity::information, "Particles", clones_arrays().ParticleSum());
    for (const int ParticleNumber : Range(clones_arrays().ParticleSum())) {
        ::delphes::GenParticle &particle = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(ParticleNumber));
        if (particle.Status < to_int(min_status)) break;
        Print(Severity::detailed, "Particles ID", particle.PID);
        int MotherId = to_int(Id::empty);
        int Mother2Id = to_int(Id::empty);
        if (particle.M1 != EmptyPosition) {
            ::delphes::GenParticle &mother = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.M1));
            MotherId = mother.PID;
        }
        if (particle.M2 != EmptyPosition) {
            ::delphes::GenParticle &mother = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.M2));
            Mother2Id = mother.PID;
        }
        Print(Severity::information, "Particles Status", "Generator");
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
