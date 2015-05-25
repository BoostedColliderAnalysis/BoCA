# include "ChargedHiggsSemiTagger.hh"

analysis::ChargedHiggsSemiTagger::ChargedHiggsSemiTagger()
{
    //     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("ChargedHiggsSemi");
    DefineVariables();
}

void analysis::ChargedHiggsSemiTagger::DefineVariables()
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

    Print(kNotification, "Variables defined");

}

analysis::ChargedHiggsSemiBranch analysis::ChargedHiggsSemiTagger::GetBranch(const Quartet31 &quartet)const
{
    Print(kInformation, "FillPairTagger", quartet.Bdt());
    ChargedHiggsSemiBranch branch;
    branch.Fill(quartet);
    return branch;
}

int analysis::ChargedHiggsSemiTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "Get Higgs Tags");

    float Mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (tag == kSignal) {
        Jets HiggsParticles = event.partons().Generator();
        HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
        if (tag == kSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        }
    }

//     Jets jets = GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());

//     Jets Leptons = event.leptons().GetTaggedJets(jet_tag);
//     const fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<Doublet> doublets = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
//     std::vector<Triplet> triplets = top_semi_tagger.GetBdt(doublets, jets, TopSemiReader);
    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event,bottom_reader_.reader());
    std::vector<Triplet> triplets = static_cast<TopSemiTagger&>(top_semi_reader_.tagger()).Triplets(event,top_semi_reader_.reader());


//     int WSemiId = w_semi_tagger.WSemiId(event);
    Jets TopParticles = event.partons().Generator();
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
        Jets  BottomParticles = event.partons().Generator();
        BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, BottomId, ChargedHiggsId);
        fastjet::PseudoJet BottomQuark;
        if (BottomParticles.size() == 1) BottomQuark = BottomParticles.front();
        else  Print(kError, "Where is the Bottom?");
        for (const auto & Jet : jets)  if (Jet.delta_R(BottomQuark) < detector_geometry().JetConeSize) BottomJets.emplace_back(Jet);
    } else BottomJets = jets;

    std::vector<Quartet31 > quartets;

    for (const auto & triplet : Finaltriplets)
        for (const auto & Jet : BottomJets) {
            if (triplet.singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            Quartet31 quartet(triplet, Jet);
            if (tag == kSignal && quartet.Jet().m() < Mass / 2)continue;
            if (tag == kSignal && quartet.Jet().m() > Mass * 3 / 2)continue;
            if (tag == kSignal && quartet.Jet().delta_R(HiggsBoson) > 2 * detector_geometry().JetConeSize) continue;
            quartets.emplace_back(quartet);
        }

    Print(kInformation, "Number of Heavy Higgses", quartets.size());

    if (tag == kSignal && quartets.size() > 1) {
        Print(kInformation, "Higgs Candidates", quartets.size());
        std::sort(quartets.begin(), quartets.end(), SortByMass(Mass));
        quartets.erase(quartets.begin() + 1, quartets.end());
    }

    return SaveEntries(quartets);
}

std::vector<analysis::Quartet31>  analysis::ChargedHiggsSemiTagger::Quartets(Event &event, const TMVA::Reader &reader)
{
    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event,bottom_reader_.reader());
    std::vector<Triplet> triplets = static_cast<TopSemiTagger&>(top_semi_reader_.tagger()).Triplets(event,top_semi_reader_.reader());

    std::vector<Quartet31> quartets;
    for (const auto & triplet : triplets)
        for (const auto & jet : jets) {
            if (triplet.singlet().delta_R(jet) < detector_geometry().JetConeSize) continue;
            Quartet31 quartet(triplet, jet);
            branch_ = GetBranch(quartet);
            quartet.SetBdt(Bdt(reader));
            quartets.emplace_back(quartet);
        }

    std::sort(quartets.begin(), quartets.end());
    quartets.erase(quartets.begin() + std::min(max_combi(), int(quartets.size())), quartets.end());
    return quartets;
}
