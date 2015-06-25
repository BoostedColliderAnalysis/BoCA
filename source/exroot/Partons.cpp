# include "exroot/Partons.hh"
# include "JetInfo.hh"

namespace analysis
{

namespace exroot
{

Partons::Partons()
{
    Print(Severity::Notification, "Constructor");
}

Jets Partons::Particles() const
{
    return Particles(Status::Stable);
}

Jets Partons::GenParticles() const
{
  return Particles(Status::Generator);
}

Jets Partons::Particles(const Status max_status) const
{
    Print(Severity::Information, "Particles", clones_arrays().ParticleSum());
    Jets particles;
    for (const int ParticleNumber : Range(clones_arrays().ParticleSum())) {
        TRootLHEFParticle &particle = static_cast<TRootLHEFParticle &>(clones_arrays().Particle(ParticleNumber));
        if (particle.Status < to_int(max_status)) break;
        Family family(particle.PID);
        Constituent constituent(LorentzVector(particle), family);
        fastjet::PseudoJet jet = PseudoJet(particle);
        jet.set_user_info(new JetInfo(constituent));
        particles.emplace_back(jet);
    }
    return particles;
}

}

}
