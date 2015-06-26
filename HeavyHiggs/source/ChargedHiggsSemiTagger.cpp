# include "ChargedHiggsSemiTagger.hh"

namespace analysis
{

  namespace heavyhiggs{

ChargedHiggsSemiTagger::ChargedHiggsSemiTagger()
{
    //     DebugLevel = Severity::debug;
    Print(Severity::notification, "Constructor");
    set_tagger_name("ChargedHiggsSemi");
    DefineVariables();
}

int ChargedHiggsSemiTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::information, "Higgs Tags");

    float mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (tag == Tag::signal) {
      Jets HiggsParticles = event.Partons().GenParticles();
      HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, Id::charged_higgs);
        if (tag == Tag::signal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(Severity::error, "Where is the Higgs?", HiggsParticles.size());
        }
    }

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Triplet> triplets = top_semi_reader_.Multiplets<TopSemiTagger>(event);


//     int WSemiId = w_semi_tagger.WSemiId(event);
    Jets TopParticles = event.Partons().GenParticles();
//     int TopSemiId = sgn(WSemiId) * std::abs(Id::top);
    int TopSemiId = top_semi_tagger_.TopSemiId(event);
    TopParticles = RemoveIfWrongParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(Severity::error, "Where is the Top?", TopParticles.size());
    std::vector<Triplet> Finaltriplets;
    if (tag == Tag::signal) {
      for (const auto & triplet : triplets) if (triplet.Jet().delta_R(TopQuark) < DetectorGeometry().JetConeSize) Finaltriplets.emplace_back(triplet);
    } else Finaltriplets = triplets;

    Jets BottomJets;
    if (tag == Tag::signal) {
      Jets  BottomParticles = event.Partons().GenParticles();
      BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, Id::bottom, Id::charged_higgs);
        fastjet::PseudoJet BottomQuark;
        if (BottomParticles.size() == 1) BottomQuark = BottomParticles.front();
        else  Print(Severity::error, "Where is the Bottom?");
        for (const auto & Jet : jets)  if (Jet.delta_R(BottomQuark) < DetectorGeometry().JetConeSize) BottomJets.emplace_back(Jet);
    } else BottomJets = jets;

    std::vector<Quartet31 > quartets;

    for (const auto & triplet : Finaltriplets)
        for (const auto & Jet : BottomJets) {
          if (triplet.SingletJet().delta_R(Jet) < DetectorGeometry().JetConeSize) continue;
            Quartet31 quartet(triplet, Jet);
            if (tag == Tag::signal && quartet.Jet().m() < mass / 2)continue;
            if (tag == Tag::signal && quartet.Jet().m() > mass * 3 / 2)continue;
            if (tag == Tag::signal && quartet.Jet().delta_R(HiggsBoson) > 2 * DetectorGeometry().JetConeSize) continue;
            quartets.emplace_back(quartet);
        }

    Print(Severity::information, "Number of Heavy Higgses", quartets.size());

    if (tag == Tag::signal && quartets.size() > 1) {
        Print(Severity::information, "Higgs Candidates", quartets.size());
        quartets = SortedByMassTo(quartets, mass);
        quartets.erase(quartets.begin() + 1, quartets.end());
    }

    return SaveEntries(quartets);
}

std::vector<Quartet31>  ChargedHiggsSemiTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
  Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
  std::vector<Triplet> triplets = top_semi_reader_.Multiplets<TopSemiTagger>(event);

    std::vector<Quartet31> quartets;
    for (const auto & triplet : triplets)
        for (const auto & jet : jets) {
          if (triplet.SingletJet().delta_R(jet) < DetectorGeometry().JetConeSize) continue;
            Quartet31 quartet(triplet, jet);
            quartet.SetBdt(Bdt(quartet,reader));
            quartets.emplace_back(quartet);
        }
    return ReduceResult(quartets);
}

  }

}
