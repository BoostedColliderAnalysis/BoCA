# include "HChargedHiggsSemiTagger.hh"

hanalysis::HChargedHiggsSemiTagger::HChargedHiggsSemiTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    set_tagger_name("ChargedHiggsSemi");
    DefineVariables();
}

void hanalysis::HChargedHiggsSemiTagger::SetTagger(
    const hanalysis::BottomTagger &NewBottomTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWHadronicTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger)
{
    bottom_tagger_ = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;

    set_tagger_name("ChargedHiggsSemi");
    DefineVariables();
}


void hanalysis::HChargedHiggsSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

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

    Print(HNotification, "Variables defined");

}

HChargedHiggsSemiBranch hanalysis::HChargedHiggsSemiTagger::GetBranch(const HQuartet31 &Quartet)const
{
    Print(HInformation, "FillPairTagger", Quartet.Bdt());
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





std::vector< HChargedHiggsSemiBranch> hanalysis::HChargedHiggsSemiTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    float Mass = Event.GetMass();
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
        HJets HiggsParticles = Event.GetParticles()->Generator();
        HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
        if (Tag == kSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(HError, "Where is the Higgs?", HiggsParticles.size());
        }
    }

    HJets Jets = GetJets(Event);
        Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader.reader());

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    const fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    std::vector<HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, Jets, TopSemiReader);


    int WSemiId = WSemiTagger.WSemiId(Event);
    HJets TopParticles = Event.GetParticles()->Generator();
    int TopSemiId = sgn(WSemiId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(HError, "Where is the Top?", TopParticles.size());
    std::vector<HTriplet> FinalTriplets;
    if (Tag == kSignal) {
        for (const auto & Triplet : Triplets) if (Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) FinalTriplets.emplace_back(Triplet);
    } else FinalTriplets = Triplets;

    HJets BottomJets;
    if (Tag == kSignal) {
    HJets  BottomParticles = Event.GetParticles()->Generator();
    BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, BottomId, ChargedHiggsId);
    fastjet::PseudoJet BottomQuark;
    if (BottomParticles.size() == 1) BottomQuark = BottomParticles.front();
    else  Print(HError, "Where is the Bottom?");
        for (const auto & Jet : Jets) if (Jet.delta_R(BottomQuark) < detector_geometry().JetConeSize) BottomJets.emplace_back(Jet);
    } else BottomJets = Jets;

    std::vector<HQuartet31 > Quartets;

    for (const auto & Triplet : FinalTriplets)
        for (const auto & Jet : BottomJets) {
            if (Triplet.Singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            HQuartet31 Quartet(Triplet, Jet);
            if (Tag == kSignal && Quartet.Jet().m() < Mass / 2)continue;
            if (Tag == kSignal && Quartet.Jet().m() > Mass * 3 / 2)continue;
            if (Tag == kSignal && Quartet.Jet().delta_R(HiggsBoson) > 2 * detector_geometry().JetConeSize) continue;
            Quartets.emplace_back(Quartet);
        }

    Print(HInformation, "Number of Heavy Higgses", Quartets.size());

    if (Tag == kSignal && Quartets.size() > 1) {
        Print(HInformation, "Higgs Candidates", Quartets.size());
        std::sort(Quartets.begin(), Quartets.end(), SortByMass(Mass));
        Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    std::vector<HChargedHiggsSemiBranch> ChargedHiggsBranches;
    for (const auto & Quartet : Quartets) ChargedHiggsBranches.emplace_back(GetBranch(Quartet));

    return ChargedHiggsBranches;
}


hanalysis::HObject::Tag hanalysis::HChargedHiggsSemiTagger::GetTag(const HQuartet31 &)
{
    Print(HInformation, "Get Sextet Tag");

    return kSignal;
}




std::vector<hanalysis::HQuartet31>  hanalysis::HChargedHiggsSemiTagger::GetBdt(const std::vector<HTriplet> Triplets , const std::vector<fastjet::PseudoJet> Siglets, const Reader &Reader)
{

    std::vector<HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
      for (const auto & Jet : Siglets) {
        if (Triplet.Singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Branch = GetBranch(Quartet);
            Quartet.SetBdt(Reader.Bdt());
            Quartets.emplace_back(Quartet);
        }

    std::sort(Quartets.begin(), Quartets.end());
    Quartets.erase(Quartets.begin() + std::min(max_combi(), int(Quartets.size())), Quartets.end());
    return Quartets;
}
