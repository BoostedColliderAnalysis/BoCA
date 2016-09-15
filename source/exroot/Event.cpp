
#include "boca/generic/Types.hh"
#include "boca/io/TreeReader.hh"
#include "boca/exroot/Classes.hh"
#include "boca/exroot/Event.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace exroot
{

std::vector<Particle> Event::Particles(Status max_status) const
{
    INFO0;
    auto particles = std::vector<Particle>{};
    for (auto const & particle : TreeReader().Array<::exroot::LHEFParticle>(Branch::particle)) {
        if (particle.Status < to_int(max_status)) break;
        particles.emplace_back(Particle(particle, particle.PID));
    }
    return particles;
}

std::vector<Lepton> Event::Electrons() const
{
    INFO0;
    auto electrons = std::vector<Lepton>{};
    for (auto const & electron : TreeReader().Array<::exroot::Electron>(Branch::electron)) electrons.emplace_back(Lepton(electron));
    return electrons;
}

std::vector<Lepton> Event::Muons() const
{
    INFO0;
    auto muons = std::vector<Lepton>{};
    for (auto const & muon : TreeReader().Array<::exroot::Muon>(Branch::muon)) muons.emplace_back(Lepton(muon));
    return muons;
}

std::vector<Photon> Event::Photons() const
{
    INFO0;
    auto photons = std::vector<Photon>{};
    for (auto const & photon : TreeReader().Array<::exroot::Photon>(Branch::photon)) photons.emplace_back(Photon(photon));
    return photons;
}

std::vector<Jet> Event::Jets() const
{
    INFO0;
    auto jets = std::vector<Jet>{};
    for (auto const & exroot_jet : TreeReader().Array<::exroot::Jet>(Branch::jet)) {
        auto jet = Jet{exroot_jet};
        jet.Info().SetBTag(exroot_jet.BTag);
        jets.emplace_back(jet);
    }
    return jets;
}

}

}
