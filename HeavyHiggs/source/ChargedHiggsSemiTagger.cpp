#include "ChargedHiggsSemiTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca {

namespace heavyhiggs {

int ChargedHiggsSemiTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    Mass mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (tag == Tag::signal) {
        Jets HiggsParticles = event.Partons().GenParticles();
        HiggsParticles = CopyIfParticle(HiggsParticles, Id::charged_higgs);
        if (tag == Tag::signal) {
            if (HiggsParticles.size() == 1)
                HiggsBoson = HiggsParticles.front();
            else
                Error(HiggsParticles.size());
        }
    }
    Jets jets = bottom_reader_.Jets(event);
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
//     int WSemiId = w_semi_tagger.WSemiId(event);
    Jets TopParticles = top_leptonic_reader_.Tagger().Particles(event);
//     TopParticles = CopyIfExactParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1)
        TopQuark = TopParticles.front();
    else
        Error(TopParticles.size());
    std::vector<Triplet> Finaltriplets;
    switch (tag) {
    case Tag::signal:
        for (auto const& triplet : triplets) if (triplet.Jet().delta_R(TopQuark) < DetectorGeometry::JetConeSize())
                Finaltriplets.emplace_back(triplet);
        break;
    case Tag::background :
        Finaltriplets = triplets;
        break;
    }
    Jets BottomJets;
    switch (tag) {
    case Tag::signal : {
        Jets  BottomParticles = event.Partons().GenParticles();
        BottomParticles = CopyIfFamily(BottomParticles, Id::bottom, Id::charged_higgs);
        fastjet::PseudoJet BottomQuark;
        if (BottomParticles.size() == 1)
            BottomQuark = BottomParticles.front();
        else
            Error(BottomParticles.size());
        for (auto const& Jet : jets)  if (Jet.delta_R(BottomQuark) < DetectorGeometry::JetConeSize())
                BottomJets.emplace_back(Jet);
        break;
    }
    case Tag::background :
        BottomJets = jets;
        break;
    }
    std::vector<Quartet31> quartets;
    for (auto const& triplet : Finaltriplets)
        for (auto const& Jet : BottomJets) {
            if (triplet.Singlet().Jet().delta_R(Jet) < DetectorGeometry::JetConeSize())
                continue;
            Quartet31 quartet(triplet, Jet);
            if (tag == Tag::signal && quartet.Mass() < mass / 2.) continue;
            if (tag == Tag::signal && quartet.Mass() > mass * 3. / 2.) continue;
            if (tag == Tag::signal && quartet.Jet().delta_R(HiggsBoson) > 2 * DetectorGeometry::JetConeSize()) continue;
            quartets.emplace_back(quartet);
        }
    Info(quartets.size());
    if (tag == Tag::signal && quartets.size() > 1) {
        Info(quartets.size());
        quartets = SortedByMassTo(quartets, mass);
        quartets.erase(quartets.begin() + 1, quartets.end());
    }
    return SaveEntries(quartets);
}

std::vector<Quartet31> ChargedHiggsSemiTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    Jets jets = bottom_reader_.Jets(event);
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    std::vector<Quartet31> quartets;
    for (auto const& triplet : triplets)
        for (auto const& jet : jets) {
            if (Close(jet)(triplet.Singlet().Jet()))
                continue;
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


