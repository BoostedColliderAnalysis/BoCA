#include "exroot/Partons.hh"

#include "exroot/ExRootAnalysis.hh"
#include "ParticleInfo.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca {

namespace exroot {

Jets Partons::Particles() const
{
    return Particles(Status::stable);
}

Jets Partons::GenParticles() const
{
    return Particles(Status::generator);
}

Jets Partons::Particles(Status max_status) const
{
//     Info(tree_reader().ParticleSum());
    Jets particles;
    for (auto const& particle : tree_reader().Objects<::exroot::LHEFParticle>(Branch::particle)) {
//         TRootLHEFParticle& particle = static_cast<TRootLHEFParticle&>(tree_reader().Particle(particle_number));
        if (particle.Status < to_int(max_status)) break;
        Family family(particle.PID);
//         Constituent constituent(LorentzVector(particle), family);
        fastjet::PseudoJet jet = PseudoJet(particle);
        jet.set_user_info(new ParticleInfo(family));
        particles.emplace_back(jet);
    }
    return particles;
}

}

}
