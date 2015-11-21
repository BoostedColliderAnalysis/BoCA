#include "exroot/Partons.hh"

#include "exroot/ExRootAnalysis.hh"
#include "ParticleInfo.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca {

namespace exroot {

  std::vector<Particle> Partons::Particles() const
{
    return Particles(Status::stable);
}

std::vector<Particle> Partons::GenParticles() const
{
    return Particles(Status::generator);
}

std::vector<Particle> Partons::Particles(Status max_status) const
{
   Info0;
   std::vector<Particle> particles;
    for (auto const& particle : tree_reader().Objects<::exroot::LHEFParticle>(Branch::particle)) {
        if (particle.Status < to_int(max_status)) break;
        particles.emplace_back(Particle(particle, particle.PID));
    }
    return particles;
}

}

}
