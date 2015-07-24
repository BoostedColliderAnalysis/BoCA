#include "ChargedHiggsSemiTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace heavyhiggs {

ChargedHiggsSemiTagger::ChargedHiggsSemiTagger()
{
    Note();
    DefineVariables();
}

int ChargedHiggsSemiTagger::Train(const Event& event, const PreCuts&, Tag tag) const
{
    Info();
    float mass = event.mass();
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
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
//     int WSemiId = w_semi_tagger.WSemiId(event);
    Jets TopParticles = event.Partons().GenParticles();
//     int TopSemiId = sgn(WSemiId) * std::abs(Id::top);
    int TopSemiId = top_leptonic_reader_.tagger().TopLeptonicId(event);
    TopParticles = CopyIfExactParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1)
        TopQuark = TopParticles.front();
    else
        Error(TopParticles.size());
    std::vector<Triplet> Finaltriplets;
    switch (tag) {
    case Tag::signal:
        for (const auto& triplet : triplets) if (triplet.Jet().delta_R(TopQuark) < DetectorGeometry::JetConeSize())
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
        for (const auto& Jet : jets)  if (Jet.delta_R(BottomQuark) < DetectorGeometry::JetConeSize())
                BottomJets.emplace_back(Jet);
        break;
    }
    case Tag::background :
        BottomJets = jets;
        break;
    }
    std::vector<Quartet31> quartets;
    for (const auto& triplet : Finaltriplets)
        for (const auto& Jet : BottomJets) {
            if (triplet.Singlet().Jet().delta_R(Jet) < DetectorGeometry::JetConeSize())
                continue;
            Quartet31 quartet(triplet, Jet);
            if (tag == Tag::signal && quartet.Jet().m() < mass / 2)
                continue;
            if (tag == Tag::signal && quartet.Jet().m() > mass * 3 / 2)
                continue;
            if (tag == Tag::signal && quartet.Jet().delta_R(HiggsBoson) > 2 * DetectorGeometry::JetConeSize())
                continue;
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

std::vector<Quartet31> ChargedHiggsSemiTagger::Multiplets(const Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const
{
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    std::vector<Quartet31> quartets;
    for (const auto& triplet : triplets)
        for (const auto& jet : jets) {
            if (Close(jet)(triplet.Singlet().Jet()))
                continue;
            Quartet31 quartet(triplet, jet);
            quartet.SetBdt(Bdt(quartet, reader));
            quartets.emplace_back(quartet);
        }
    return ReduceResult(quartets);
}

}

}


