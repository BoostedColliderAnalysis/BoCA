# include "ChargedHiggsSemiTagger.hh"

namespace analysis
{

  namespace heavyhiggs{

ChargedHiggsSemiTagger::ChargedHiggsSemiTagger()
{
    //     DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("ChargedHiggsSemi");
    DefineVariables();
}

int ChargedHiggsSemiTagger::Train(Event &event, const Tag tag)
{
    Print(kInformation, "Higgs Tags");

    float mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (tag == kSignal) {
      Jets HiggsParticles = event.Partons().GenParticles();
      HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
        if (tag == kSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        }
    }

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Triplet> triplets = top_semi_reader_.Multiplets<TopSemiTagger>(event);


//     int WSemiId = w_semi_tagger.WSemiId(event);
    Jets TopParticles = event.Partons().GenParticles();
//     int TopSemiId = sgn(WSemiId) * std::abs(TopId);
    int TopSemiId = top_semi_tagger_.TopSemiId(event);
    TopParticles = RemoveIfWrongParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(kError, "Where is the Top?", TopParticles.size());
    std::vector<Triplet> Finaltriplets;
    if (tag == kSignal) {
        for (const auto & triplet : triplets) if (triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) Finaltriplets.emplace_back(triplet);
    } else Finaltriplets = triplets;

    Jets BottomJets;
    if (tag == kSignal) {
      Jets  BottomParticles = event.Partons().GenParticles();
      BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, BottomId, ChargedHiggsId);
        fastjet::PseudoJet BottomQuark;
        if (BottomParticles.size() == 1) BottomQuark = BottomParticles.front();
        else  Print(kError, "Where is the Bottom?");
        for (const auto & Jet : jets)  if (Jet.delta_R(BottomQuark) < detector_geometry().JetConeSize) BottomJets.emplace_back(Jet);
    } else BottomJets = jets;

    std::vector<Quartet31 > quartets;

    for (const auto & triplet : Finaltriplets)
        for (const auto & Jet : BottomJets) {
            if (triplet.SingletJet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            Quartet31 quartet(triplet, Jet);
            if (tag == kSignal && quartet.Jet().m() < mass / 2)continue;
            if (tag == kSignal && quartet.Jet().m() > mass * 3 / 2)continue;
            if (tag == kSignal && quartet.Jet().delta_R(HiggsBoson) > 2 * detector_geometry().JetConeSize) continue;
            quartets.emplace_back(quartet);
        }

    Print(kInformation, "Number of Heavy Higgses", quartets.size());

    if (tag == kSignal && quartets.size() > 1) {
        Print(kInformation, "Higgs Candidates", quartets.size());
        quartets = SortedByMassTo(quartets, mass);
        quartets.erase(quartets.begin() + 1, quartets.end());
    }

    return SaveEntries(quartets);
}

std::vector<Quartet31>  ChargedHiggsSemiTagger::Multiplets(Event& event, const TMVA::Reader& reader)
{
  Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
  std::vector<Triplet> triplets = top_semi_reader_.Multiplets<TopSemiTagger>(event);

    std::vector<Quartet31> quartets;
    for (const auto & triplet : triplets)
        for (const auto & jet : jets) {
            if (triplet.SingletJet().delta_R(jet) < detector_geometry().JetConeSize) continue;
            Quartet31 quartet(triplet, jet);
            quartet.SetBdt(Bdt(quartet,reader));
            quartets.emplace_back(quartet);
        }
    return ReduceResult(quartets);
}

  }

}
