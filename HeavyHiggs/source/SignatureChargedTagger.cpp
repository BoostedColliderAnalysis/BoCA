#include "SignatureChargedTagger.hh"
#include "Event.hh"
#include "multiplets/Particles.hh"
#include "generic/DEBUG.hh"

namespace boca {

namespace heavyhiggs {

int SignatureChargedTagger::Train(Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    auto higgs_quartets = charged_higgs_semi_reader_.Multiplets(event);
   auto HiggsParticles = event.Partons().GenParticles();
    HiggsParticles = CopyIfParticle(HiggsParticles, Id::charged_higgs);
    if (tag == Tag::signal && HiggsParticles.size() != 1) ERROR("Where is the Higgs?");
    SortedByMinDeltaRTo(higgs_quartets, HiggsParticles.front());
    if (tag == Tag::signal && higgs_quartets.size() > 1) higgs_quartets.erase(higgs_quartets.begin() + 1, higgs_quartets.end());
    auto jet_quartets = triplet_jet_pair_reader_.Multiplets(event);
    std::vector<Octet44> octets;
    for (auto const& higgs_quartet  : higgs_quartets)
        for (auto const& jet_quartet : jet_quartets) {
            Octet44 octet(higgs_quartet, jet_quartet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    return SaveEntries(octets);
}


std::vector<Octet44> SignatureChargedTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    auto higgs_quartets = charged_higgs_semi_reader_.Multiplets(event);
    auto jet_quartets = triplet_jet_pair_reader_.Multiplets(event);
    std::vector<Octet44> octets;
    for (auto const& jet_quartet : jet_quartets) {
        for (auto const& higgs_quartet : higgs_quartets) {
            Octet44 octet(higgs_quartet, jet_quartet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
    return octets;
}
std::string SignatureChargedTagger::Name() const
{
    return "SignatureCharged";
}

}

}
