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
    const analysis::HWSemiTagger &NewWSemiTagger,
    const analysis::WHadronicTagger &NewWTagger,
    const analysis::HTopSemiTagger &NewTopSemiTagger,
    const analysis::TopHadronicTagger &Newtop_hadronic_tagger)
{
    bottom_tagger_ = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
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

HChargedHiggsSemiBranch analysis::HChargedHiggsSemiTagger::GetBranch(const HQuartet31 &Quartet)const
{
    Print(kInformation, "FillPairTagger", Quartet.Bdt());
    HChargedHiggsSemiBranch ChargedHiggsBranch;
    ChargedHiggsBranch.Mass = Quartet.Jet().m();
    ChargedHiggsBranch.Rap = Quartet.Jet().rap();
    ChargedHiggsBranch.Phi = Quartet.Jet().phi();
    ChargedHiggsBranch.Pt = Quartet.Jet().pt();
    ChargedHiggsBranch.Ht = Quartet.Ht();

    ChargedHiggsBranch.DeltaPt = Quartet.DeltaPt();
    ChargedHiggsBranch.DeltaM = Quartet.DeltaM();
    ChargedHiggsBranch.DeltaHt = Quartet.DeltaHt();
    ChargedHiggsBranch.DeltaR = Quartet.DeltaR();
    ChargedHiggsBranch.DeltaRap = Quartet.DeltaRap();
    ChargedHiggsBranch.DeltaPhi = Quartet.DeltaPhi();

    ChargedHiggsBranch.Bdt = Quartet.Bdt();
    ChargedHiggsBranch.Tag = Quartet.Tag();
    ChargedHiggsBranch.Flag = Quartet.Flag();
    return ChargedHiggsBranch;

}





std::vector< HChargedHiggsSemiBranch> analysis::HChargedHiggsSemiTagger::GetBranches(analysis::Event &event, const analysis::Object::Tag Tag)
{
    Print(kInformation, "Get Higgs Tags");

    float Mass = event.mass();
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
        Jets HiggsParticles = event.Partons().Generator();
        HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
        if (Tag == kSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        }
    }

    Jets jets = GetJets(event);
        jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());

    Jets Leptons = event.Leptons().GetTaggedJets(JetTag);
    const fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    std::vector<Triplet> triplets = TopSemiTagger.GetBdt(doublets, jets, TopSemiReader);


    int WSemiId = WSemiTagger.WSemiId(event);
    Jets TopParticles = event.Partons().Generator();
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
    Jets  BottomParticles = event.Partons().Generator();
    BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, BottomId, ChargedHiggsId);
    fastjet::PseudoJet BottomQuark;
    if (BottomParticles.size() == 1) BottomQuark = BottomParticles.front();
    else  Print(kError, "Where is the Bottom?");
        for (const auto & Jet : jets)  if (Jet.delta_R(BottomQuark) < detector_geometry().JetConeSize) BottomJets.emplace_back(Jet);
    } else BottomJets = jets;

    std::vector<HQuartet31 > Quartets;

    for (const auto & triplet : Finaltriplets)
        for (const auto & Jet : BottomJets) {
            if (triplet.singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            HQuartet31 Quartet(triplet, Jet);
            if (Tag == kSignal && Quartet.Jet().m() < Mass / 2)continue;
            if (Tag == kSignal && Quartet.Jet().m() > Mass * 3 / 2)continue;
            if (Tag == kSignal && Quartet.Jet().delta_R(HiggsBoson) > 2 * detector_geometry().JetConeSize) continue;
            Quartets.emplace_back(Quartet);
        }

    Print(kInformation, "Number of Heavy Higgses", Quartets.size());

    if (Tag == kSignal && Quartets.size() > 1) {
        Print(kInformation, "Higgs Candidates", Quartets.size());
        std::sort(Quartets.begin(), Quartets.end(), SortByMass(Mass));
        Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    std::vector<HChargedHiggsSemiBranch> ChargedHiggsBranches;
    for (const auto & Quartet : Quartets) ChargedHiggsBranches.emplace_back(GetBranch(Quartet));

    return ChargedHiggsBranches;
}


analysis::Object::Tag analysis::HChargedHiggsSemiTagger::GetTag(const HQuartet31 &)
{
    Print(kInformation, "Get Sextet Tag");

    return kSignal;
}




std::vector<analysis::HQuartet31>  analysis::HChargedHiggsSemiTagger::GetBdt(const std::vector<Triplet> triplets , const std::vector<fastjet::PseudoJet> Siglets, const Reader &Reader)
{

    std::vector<HQuartet31> Quartets;
    for (const auto & triplet : triplets)
      for (const auto & Jet : Siglets) {
        if (triplet.singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            HQuartet31 Quartet(triplet, Jet);
            Branch = GetBranch(Quartet);
            Quartet.SetBdt(Reader.Bdt());
            Quartets.emplace_back(Quartet);
        }

    std::sort(Quartets.begin(), Quartets.end());
    Quartets.erase(Quartets.begin() + std::min(max_combi(), int(Quartets.size())), Quartets.end());
    return Quartets;
}
