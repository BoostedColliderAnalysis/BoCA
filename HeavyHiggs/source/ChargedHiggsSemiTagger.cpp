# include "ChargedHiggsSemiTagger.hh"

heavyhiggs::ChargedHiggsSemiTagger::ChargedHiggsSemiTagger()
{
    //     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("ChargedHiggsSemi");
    DefineVariables();
}

void heavyhiggs::ChargedHiggsSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");
    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
    AddSpectator(branch_.Flag, "Flag");
}

int heavyhiggs::ChargedHiggsSemiTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "Higgs Tags");

    float mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (tag == kSignal) {
      analysis::Jets HiggsParticles = event.Partons().GenParticles();
      HiggsParticles = analysis::RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
        if (tag == kSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        }
    }

    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    std::vector<analysis::Triplet> triplets = top_semi_reader_.Multiplets<analysis::TopSemiTagger>(event);


//     int WSemiId = w_semi_tagger.WSemiId(event);
    analysis::Jets TopParticles = event.Partons().GenParticles();
//     int TopSemiId = sgn(WSemiId) * std::abs(TopId);
    int TopSemiId = top_semi_tagger_.TopSemiId(event);
    TopParticles = analysis::RemoveIfWrongParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(kError, "Where is the Top?", TopParticles.size());
    std::vector<analysis::Triplet> Finaltriplets;
    if (tag == kSignal) {
        for (const auto & triplet : triplets) if (triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) Finaltriplets.emplace_back(triplet);
    } else Finaltriplets = triplets;

    analysis::Jets BottomJets;
    if (tag == kSignal) {
      analysis::Jets  BottomParticles = event.Partons().GenParticles();
      BottomParticles = analysis::RemoveIfWrongAbsFamily(BottomParticles, BottomId, ChargedHiggsId);
        fastjet::PseudoJet BottomQuark;
        if (BottomParticles.size() == 1) BottomQuark = BottomParticles.front();
        else  Print(kError, "Where is the Bottom?");
        for (const auto & Jet : jets)  if (Jet.delta_R(BottomQuark) < detector_geometry().JetConeSize) BottomJets.emplace_back(Jet);
    } else BottomJets = jets;

    std::vector<analysis::Quartet31 > quartets;

    for (const auto & triplet : Finaltriplets)
        for (const auto & Jet : BottomJets) {
            if (triplet.SingletJet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            analysis::Quartet31 quartet(triplet, Jet);
            if (tag == kSignal && quartet.Jet().m() < mass / 2)continue;
            if (tag == kSignal && quartet.Jet().m() > mass * 3 / 2)continue;
            if (tag == kSignal && quartet.Jet().delta_R(HiggsBoson) > 2 * detector_geometry().JetConeSize) continue;
            quartets.emplace_back(quartet);
        }

    Print(kInformation, "Number of Heavy Higgses", quartets.size());

    if (tag == kSignal && quartets.size() > 1) {
        Print(kInformation, "Higgs Candidates", quartets.size());
        quartets = analysis::SortedByMassTo(quartets, mass);
        quartets.erase(quartets.begin() + 1, quartets.end());
    }

    return SaveEntries<ChargedHiggsSemiBranch>(quartets);
}

std::vector<analysis::Quartet31>  heavyhiggs::ChargedHiggsSemiTagger::Multiplets(analysis::Event& event, const TMVA::Reader& reader)
{
  analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
  std::vector<analysis::Triplet> triplets = top_semi_reader_.Multiplets<analysis::TopSemiTagger>(event);

    std::vector<analysis::Quartet31> quartets;
    for (const auto & triplet : triplets)
        for (const auto & jet : jets) {
            if (triplet.SingletJet().delta_R(jet) < detector_geometry().JetConeSize) continue;
            analysis::Quartet31 quartet(triplet, jet);
            branch_ = branch<ChargedHiggsSemiBranch>(quartet);
            quartet.SetBdt(Bdt(reader));
            quartets.emplace_back(quartet);
        }
    return ReduceResult(quartets);
}
