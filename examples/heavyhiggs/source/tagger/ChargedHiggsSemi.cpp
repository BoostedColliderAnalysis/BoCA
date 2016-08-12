#include "boca/Event.hh"
#include "boca/multiplets/Particles.hh"

#include "include/tagger/ChargedHiggsSemi.hh"

#include "boca/generic/DEBUG_MACROS.hh"

namespace heavyhiggs
{

namespace tagger
{

int ChargedHiggsSemi::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
//     Mass mass = event.mass();
    boca::Jet HiggsBoson;
    if (tag == Tag::signal) {
        auto HiggsParticles = event.GenParticles();
        HiggsParticles = CopyIfParticle(HiggsParticles, Id::charged_higgs);
        if (tag == Tag::signal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else ERROR(HiggsParticles.size());
        }
    }
    auto jets = bottom_reader_.Jets(event);
    auto triplets = top_leptonic_reader_.Multiplets(event);
//     int WSemiId = w_semi_tagger.WSemiId(event);
    auto TopParticles = top_leptonic_reader_.Tagger().Particles(event);
//     TopParticles = CopyIfExactParticle(TopParticles, TopSemiId);
    Particle TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else
        ERROR(TopParticles.size());
    std::vector<Triplet> Finaltriplets;
    switch (tag) {
    case Tag::signal:
        for (auto const & triplet : triplets) if (triplet.DeltaRTo(TopQuark) < Settings::JetConeSize()) Finaltriplets.emplace_back(triplet);
        break;
    case Tag::background :
        Finaltriplets = triplets;
        break;
    }
    std::vector<boca::Jet> BottomJets;
    switch (tag) {
    case Tag::signal : {
        auto BottomParticles = event.GenParticles();
        BottomParticles = CopyIfFamily(BottomParticles, Id::bottom, Id::charged_higgs);
        boca::Jet BottomQuark;
        if (BottomParticles.size() == 1) BottomQuark = BottomParticles.front();
        else ERROR(BottomParticles.size());
        for (auto const & Jet : jets)  if (Jet.DeltaRTo(BottomQuark) < Settings::JetConeSize()) BottomJets.emplace_back(Jet);
        break;
    }
    case Tag::background :
        BottomJets = jets;
        break;
    }
    std::vector<Quartet31> quartets;
    for (auto const & triplet : Finaltriplets)
        for (auto const & Jet : BottomJets) {
            if (triplet.DeltaRTo(Jet) < Settings::JetConeSize()) continue;
            Quartet31 quartet(triplet, Jet);
//             if (tag == Tag::signal && quartet.Mass() < mass / 2.) continue;
//             if (tag == Tag::signal && quartet.Mass() > mass * 3. / 2.) continue;
            if (tag == Tag::signal && quartet.DeltaRTo(HiggsBoson) > 2. * Settings::JetConeSize()) continue;
            quartets.emplace_back(quartet);
        }
    INFO(quartets.size());
    if (tag == Tag::signal && quartets.size() > 1) {
        INFO(quartets.size());
//         quartets = SortedByMassTo(quartets, mass);
        quartets.erase(quartets.begin() + 1, quartets.end());
    }
    return SaveEntries(quartets);
}

std::vector<Quartet31> ChargedHiggsSemi::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    auto jets = bottom_reader_.Jets(event);
    auto triplets = top_leptonic_reader_.Multiplets(event);
    std::vector<Quartet31> quartets;
    for (auto const & triplet : triplets)
        for (auto const & jet : jets) {
            if (Close<boca::Jet>(jet)(triplet.Singlet())) continue;
            Quartet31 quartet(triplet, jet);
            quartet.SetBdt(Bdt(quartet, reader));
            quartets.emplace_back(quartet);
        }
    return quartets;
}
std::string ChargedHiggsSemi::Name() const
{
    return "ChargedHiggsSemi";
}

}

}


