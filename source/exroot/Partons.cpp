#include "exroot/Partons.hh"

#include "exroot/ExRootAnalysis.hh"
#include "generic/Types.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace exroot
{

Partons::Partons(boca::TreeReader const& tree_reader) :
    boca::Partons(tree_reader) {}

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
    INFO0;
    std::vector<Particle> particles;
    for (auto const & particle : TreeReader().Array<::exroot::LHEFParticle>(Branch::particle)) {
        if (particle.Status < to_int(max_status)) break;
        particles.emplace_back(Particle(particle, particle.PID));
    }
    return particles;
}

}

}
