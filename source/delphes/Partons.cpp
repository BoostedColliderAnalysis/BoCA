# include "delphes/Partons.hh"
# include "Predicate.hh"

namespace analysis
{

namespace delphes
{

Partons::Partons()
{
//     DebugLevel = Object::kDebug;
    Print(kDebug, "Constructor");
}

Jets Partons::Particles() const
{
    return Particles(kStable);
}

Jets Partons::GenParticles() const
{
    return Particles(kGenerator);
}

Jets Partons::Particles(const Object::Status min_status) const
{
    Jets particles;
    Print(kInformation, "Particles", clones_arrays().ParticleSum());
    for (const int ParticleNumber : Range(clones_arrays().ParticleSum())) {
        ::delphes::GenParticle &particle = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(ParticleNumber));
        if (particle.Status < min_status) break;
        Print(kDetailed, "Particles ID", particle.PID);
        int MotherId = EmptyId;
        int Mother2Id = EmptyId;
        if (particle.M1 != EmptyPosition) {
            ::delphes::GenParticle &mother = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.M1));
            MotherId = mother.PID;
        }
        if (particle.M2 != EmptyPosition) {
            ::delphes::GenParticle &mother = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.M2));
            Mother2Id = mother.PID;
        }
        Print(kInformation, "Particles Status", "Generator");
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