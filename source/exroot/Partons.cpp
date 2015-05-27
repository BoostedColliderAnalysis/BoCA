# include "exroot/Partons.hh"

analysis::exroot::Partons::Partons()
{
    Print(kNotification, "Constructor");
}

analysis::Jets analysis::exroot::Partons::Particles() const
{
    return Particles(kStable);
}

analysis::Jets analysis::exroot::Partons::GenParticles() const
{
    return Particles(kGenerator);
}

analysis::Jets analysis::exroot::Partons::Particles(const analysis::Object::Status max_status) const
{
    Print(kInformation, "Particles", clones_arrays().ParticleSum());
    Jets particles;
    for (const int ParticleNumber : Range(clones_arrays().ParticleSum())) {
        TRootLHEFParticle &particle = static_cast<TRootLHEFParticle &>(clones_arrays().Particle(ParticleNumber));
        if (particle.Status < max_status) break;
        Family family(particle.PID);
        Constituent constituent(LorentzVector(particle), family);
        fastjet::PseudoJet jet = PseudoJet(particle);
        jet.set_user_info(new JetInfo(constituent));
        particles.emplace_back(jet);
    }
    return particles;
}
