
#include <boost/range/numeric.hpp>

#include "boca/generic/Types.hh"
#include "boca/io/TreeReader.hh"
#include "boca/exroot/Classes.hh"
#include "boca/exroot/Event.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace exroot
{

std::vector<Particle> Event::GetParticles(Status max_status) const
{
    INFO0;
    auto particles = std::vector<Particle> {};
    for (auto const & particle : TreeReader().Array<::exroot::LHEFParticle>(Branch::particle)) {
        if (particle.Status < to_int(max_status)) break;
        particles.emplace_back(Particle(particle, particle.PID));
    }
    return particles;
}

std::vector<Lepton> Event::GetElectrons() const
{
    INFO0;
    auto electrons = std::vector<Lepton> {};
    for (auto const & electron : TreeReader().Array<::exroot::Electron>(Branch::electron)) electrons.emplace_back(Lepton(electron));
    return electrons;
}

std::vector<Lepton> Event::GetMuons() const
{
    INFO0;
    auto muons = std::vector<Lepton> {};
    for (auto const & muon : TreeReader().Array<::exroot::Muon>(Branch::muon)) muons.emplace_back(Lepton(muon));
    return muons;
}

std::vector<Photon> Event::GetPhotons() const
{
    INFO0;
    auto photons = std::vector<Photon> {};
    for (auto const & photon : TreeReader().Array<::exroot::Photon>(Branch::photon)) photons.emplace_back(Photon(photon));
    return photons;
}

std::vector<Jet> Event::GetJets() const
{
    INFO0;
    auto jets = std::vector<Jet> {};
    for (auto const & exroot_jet : TreeReader().Array<::exroot::Jet>(Branch::jet)) {
        auto jet = Jet {exroot_jet};
        jet.Info().SetBTag(exroot_jet.BTag);
        jets.emplace_back(jet);
    }
    return jets;
}

std::vector<Jet> Event::GetEFlow(JetDetail) const {
    return Jets();
}

boca::MissingEt Event::GetMissingEt() const {
    return boost::accumulate(Leptons(),Lepton {}, [](Lepton & sum, Lepton const& jet) {
        return sum - Lepton(jet.Px(), jet.Py(), 0_eV, 0_eV);
    });
}

Momentum Event::GetScalarHt() const {
    return boost::accumulate(Jets(),at_rest,[](Momentum & sum, Jet const& jet) {
        return sum + jet.Pt();
    });
}

}

}
