# include "HChargedHiggsSemiTagger.hh"

analysis::HChargedHiggsSemiTagger::HChargedHiggsSemiTagger()
{
    //     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("ChargedHiggsSemi");
    DefineVariables();
}

void analysis::HChargedHiggsSemiTagger::SetTagger(
    const analysis::BottomTagger &NewBottomTagger,
    const analysis::WSemiTagger &Neww_semi_tagger,
    const analysis::WHadronicTagger &NewWTagger,
    const analysis::TopSemiTagger &Newtop_semi_tagger,
    const analysis::TopHadronicTagger &Newtop_hadronic_tagger)
{
    bottom_tagger_ = NewBottomTagger;
    w_semi_tagger = Neww_semi_tagger;
    WTagger = NewWTagger;
    top_semi_tagger = Newtop_semi_tagger;
    top_hadronic_tagger = Newtop_hadronic_tagger;

    set_tagger_name("ChargedHiggsSemi");
    DefineVariables();
}


void analysis::HChargedHiggsSemiTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

    ClearVectors();


    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Ht, "Ht");

    AddVariable(Branch.DeltaPt, "DeltaPt");
    AddVariable(Branch.DeltaM, "DeltaM");
    AddVariable(Branch.DeltaHt, "DeltaHt");
    AddVariable(Branch.DeltaR, "DeltaR");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");

    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");
    AddSpectator(Branch.Flag, "Flag");

    Print(kNotification, "Variables defined");

}

analysis::HChargedHiggsSemiBranch analysis::HChargedHiggsSemiTagger::GetBranch(const Quartet31 &quartet)const
{
    Print(kInformation, "FillPairTagger", quartet.Bdt());
    HChargedHiggsSemiBranch ChargedHiggsBranch;
    ChargedHiggsBranch.Mass = quartet.Jet().m();
    ChargedHiggsBranch.Rap = quartet.Jet().rap();
    ChargedHiggsBranch.Phi = quartet.Jet().phi();
    ChargedHiggsBranch.Pt = quartet.Jet().pt();
    ChargedHiggsBranch.Ht = quartet.Ht();

    ChargedHiggsBranch.DeltaPt = quartet.DeltaPt();
    ChargedHiggsBranch.DeltaM = quartet.DeltaM();
    ChargedHiggsBranch.DeltaHt = quartet.DeltaHt();
    ChargedHiggsBranch.DeltaR = quartet.DeltaR();
    ChargedHiggsBranch.DeltaRap = quartet.DeltaRap();
    ChargedHiggsBranch.DeltaPhi = quartet.DeltaPhi();

    ChargedHiggsBranch.Bdt = quartet.Bdt();
    ChargedHiggsBranch.Tag = quartet.Tag();
    ChargedHiggsBranch.Flag = quartet.Flag();
    return ChargedHiggsBranch;

}





std::vector< analysis::HChargedHiggsSemiBranch> analysis::HChargedHiggsSemiTagger::GetBranches(analysis::Event &event, const analysis::Object::Tag Tag)
{
    Print(kInformation, "Get Higgs Tags");

    float Mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
        Jets HiggsParticles = event.partons().Generator();
        HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
        if (Tag == kSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        }
    }

    Jets jets = GetJets(event);
        jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());

    Jets Leptons = event.leptons().GetTaggedJets(jet_tag);
    const fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<Doublet> doublets = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    std::vector<Triplet> triplets = top_semi_tagger.GetBdt(doublets, jets, TopSemiReader);


    int WSemiId = w_semi_tagger.WSemiId(event);
    Jets TopParticles = event.partons().Generator();
    int TopSemiId = sgn(WSemiId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(kError, "Where is the Top?", TopParticles.size());
    std::vector<Triplet> Finaltriplets;
    if (Tag == kSignal) {
        for (const auto & triplet : triplets) if (triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) Finaltriplets.emplace_back(triplet);
    } else Finaltriplets = triplets;

    Jets BottomJets;
    if (Tag == kSignal) {
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
            if (Tag == kSignal && quartet.Jet().m() < Mass / 2)continue;
            if (Tag == kSignal && quartet.Jet().m() > Mass * 3 / 2)continue;
            if (Tag == kSignal && quartet.Jet().delta_R(HiggsBoson) > 2 * detector_geometry().JetConeSize) continue;
            quartets.emplace_back(quartet);
        }

    Print(kInformation, "Number of Heavy Higgses", quartets.size());

    if (Tag == kSignal && quartets.size() > 1) {
        Print(kInformation, "Higgs Candidates", quartets.size());
        std::sort(quartets.begin(), quartets.end(), SortByMass(Mass));
        quartets.erase(quartets.begin() + 1, quartets.end());
    }

    std::vector<HChargedHiggsSemiBranch> ChargedHiggsBranches;
    for (const auto & quartet : quartets) ChargedHiggsBranches.emplace_back(GetBranch(quartet));

    return ChargedHiggsBranches;
}


analysis::Object::Tag analysis::HChargedHiggsSemiTagger::GetTag(const Quartet31 &)
{
    Print(kInformation, "Get sextet Tag");

    return kSignal;
}




std::vector<analysis::Quartet31>  analysis::HChargedHiggsSemiTagger::GetBdt(const std::vector<Triplet> triplets , const std::vector<fastjet::PseudoJet> Siglets, const Reader &Reader)
{

    std::vector<Quartet31> quartets;
    for (const auto & triplet : triplets)
      for (const auto & Jet : Siglets) {
        if (triplet.singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            Quartet31 quartet(triplet, Jet);
            Branch = GetBranch(quartet);
            quartet.SetBdt(Reader.Bdt());
            quartets.emplace_back(quartet);
        }

    std::sort(quartets.begin(), quartets.end());
    quartets.erase(quartets.begin() + std::min(max_combi(), int(quartets.size())), quartets.end());
    return quartets;
}
