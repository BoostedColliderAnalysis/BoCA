#include "ChargedHiggsSemiTagger.hh"
#include "Event.hh"
#include "DEBUG.hh"

namespace boca {

namespace heavyhiggs {

int ChargedHiggsSemiTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
//     Mass mass = event.mass();
    Jet HiggsBoson;
    if (tag == Tag::signal) {
       std::vector<Particle> HiggsParticles = event.Partons().GenParticles();
        HiggsParticles = CopyIfParticle(HiggsParticles, Id::charged_higgs);
        if (tag == Tag::signal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else ERROR(HiggsParticles.size());
        }
    }
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
//     int WSemiId = w_semi_tagger.WSemiId(event);
   std::vector<Particle> TopParticles = top_leptonic_reader_.Tagger().Particles(event);
//     TopParticles = CopyIfExactParticle(TopParticles, TopSemiId);
    Particle TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else
        ERROR(TopParticles.size());
    std::vector<Triplet> Finaltriplets;
    switch (tag) {
    case Tag::signal:
        for (auto const& triplet : triplets) if (triplet.DeltaRTo(TopQuark) < DetectorGeometry::JetConeSize()) Finaltriplets.emplace_back(triplet);
        break;
    case Tag::background :
        Finaltriplets = triplets;
        break;
    }
   std::vector<Jet> BottomJets;
    switch (tag) {
    case Tag::signal : {
      std::vector<Particle> BottomParticles = event.Partons().GenParticles();
        BottomParticles = CopyIfFamily(BottomParticles, Id::bottom, Id::charged_higgs);
        Jet BottomQuark;
        if (BottomParticles.size() == 1) BottomQuark = BottomParticles.front();
        else ERROR(BottomParticles.size());
        for (auto const& Jet : jets)  if (Jet.DeltaRTo(BottomQuark) < DetectorGeometry::JetConeSize()) BottomJets.emplace_back(Jet);
        break;
    }
    case Tag::background :
        BottomJets = jets;
        break;
    }
    std::vector<Quartet31> quartets;
    for (auto const& triplet : Finaltriplets)
        for (auto const& Jet : BottomJets) {
            if (triplet.DeltaRTo(Jet) < DetectorGeometry::JetConeSize()) continue;
            Quartet31 quartet(triplet, Jet);
//             if (tag == Tag::signal && quartet.Mass() < mass / 2.) continue;
//             if (tag == Tag::signal && quartet.Mass() > mass * 3. / 2.) continue;
            if (tag == Tag::signal && quartet.DeltaRTo(HiggsBoson) > 2. * DetectorGeometry::JetConeSize()) continue;
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

std::vector<Quartet31> ChargedHiggsSemiTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    std::vector<Quartet31> quartets;
    for (auto const& triplet : triplets)
        for (auto const& jet : jets) {
            if (Close(jet)(triplet.Singlet())) continue;
            Quartet31 quartet(triplet, jet);
            quartet.SetBdt(Bdt(quartet, reader));
            quartets.emplace_back(quartet);
        }
    return ReduceResult(quartets);
}
std::string ChargedHiggsSemiTagger::Name() const
{
    return "ChargedHiggsSemi";
}

}

}


