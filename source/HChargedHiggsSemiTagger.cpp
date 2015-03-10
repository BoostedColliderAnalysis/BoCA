# include "HChargedHiggsSemiTagger.hh"

hanalysis::HChargedHiggsSemiTagger::HChargedHiggsSemiTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    SetTaggerName("ChargedHiggsSemi");
    DefineVariables();
}

hanalysis::HChargedHiggsSemiTagger::~HChargedHiggsSemiTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HChargedHiggsSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger)
{
    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;

    SetTaggerName("ChargedHiggsSemi");
    DefineVariables();
}


void hanalysis::HChargedHiggsSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));
    Spectators.push_back(NewObservable(&Branch.Flag, "Flag"));

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
    ChargedHiggsBranch.DeltaR = Quartet.DeltaR();
    ChargedHiggsBranch.DeltaRap = Quartet.DeltaRap();
    ChargedHiggsBranch.DeltaPhi = Quartet.DeltaPhi();

    ChargedHiggsBranch.Bdt = Quartet.Bdt();
    ChargedHiggsBranch.Tag = Quartet.Tag();
    ChargedHiggsBranch.Flag = Quartet.Flag();
    return ChargedHiggsBranch;

}





std::vector< HChargedHiggsSemiBranch> hanalysis::HChargedHiggsSemiTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    float Mass = Event.GetMass();
    JetTag.HeavyParticles = {ChargedHiggsId};
//     HJets Jets = Event.GetJets()->GetStructuredTaggedJets(JetTag);

    HJets Jets = GetJets(Event,JetTag);

    HJets BottomJets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    const fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);

    std::vector<HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, BottomJets, TopSemiReader);

//     std::vector<HTriplet> Triplets;
// for(const auto &Jet : Jets) Triplets.push_back(HTriplet(Jet));

//     for (const auto & Lepton : Leptons) {
//         HDoublet Doublet(Lepton);
//         for (const auto & Jet : Jets) {
//             Triplets.push_back(HTriplet(Doublet,Jet));
//         }
//     }

    std::vector<HQuartet31 > Quartets;
//     HTriplet Triplet;
//     if (Tag == HSignal) {
    HJets TopParticles = Event.GetParticles()->Generator();
    TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongAbsFamily(TopId, ChargedHiggsId)), TopParticles.end());
    if (TopParticles.size() != 1) {
        Print(HError, "Where is the Top?", TopParticles.size());
    } else {
        std::sort(Triplets.begin(), Triplets.end(), MinDeltaR(TopParticles.front()));
//         if (Tag == HSignal && Triplets.size() > 2) {
//             Triplets.erase(Triplets.begin() + 2, Triplets.end());
//         } else
        if (Tag == HSignal && Triplets.size() > 1) {
            Triplets.erase(Triplets.begin() + 1, Triplets.end()) ;
        }
//         if (Tag == HBackground && Triplets.size() > 0) Triplets.erase(Triplets.begin());
//         if (Triplets.size() > 0) Triplet=HTriplet(Particles.front());
    }

//     if (Tag == HSignal) {
    HJets  BottomParticles = Event.GetParticles()->Generator();
    BottomParticles.erase(std::remove_if(BottomParticles.begin(), BottomParticles.end(), WrongAbsFamily(BottomId, ChargedHiggsId)), BottomParticles.end());
    if (BottomParticles.size() != 1) {
        Print(HError, "Where is the Bottom?");
    } else {
        std::sort(BottomJets.begin(), BottomJets.end(), MinDeltaR(BottomParticles.front()));
//         if (Tag == HSignal && BottomJets.size() > 2) {
//             BottomJets.erase(BottomJets.begin() + 2, BottomJets.end());
//         } else
          if (Tag == HSignal && BottomJets.size() > 1) {
            BottomJets.erase(BottomJets.begin() + 1, BottomJets.end());
        }
//         if (Tag == HBackground && BottomJets.size() > 0) BottomJets.erase(BottomJets.begin());
//         if (Jets.size() > 0) Quartets.push_back(HQuartet31(Triplet,Particles.front()));
    }





//     std::vector<HDoublet> DoubletsHadronic = TopHadronicTagger.WTagger.GetBdt(Jets, TopHadronicTagger.WReader);
//     std::vector<HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
//     std::vector<HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
//     Triplets.insert(Triplets.end(), TripletsHadronic.begin(), TripletsHadronic.end());

//     if (Tag == HBackground) {
//         for (const auto & Triplet : Triplets)
//             for (const auto & Jet : Jets) {
//                 if (Triplet.Singlet() == Jet) continue;
//                 if (Triplet.Doublet().Singlet1() == Jet) continue;
//                 if (Triplet.Doublet().Singlet2() == Jet) continue;
//                 HQuartet31 Quartet(Triplet, Jet);
//                 Quartet.SetTag(GetTag(Quartet));
//                 if (Quartet.Tag() != Tag) continue;
//                 if (Tag == HSignal && Quartet.Jet().m() < Mass / 2)continue;
//                 Quartets.push_back(Quartet);
//             }
//     } else {
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : BottomJets) {
            if (Triplet.Singlet() == Jet) continue;
//           if (Triplet.Doublet().Singlet1() == Jet) continue;
//           if (Triplet.Doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
//           Quartet.SetTag(GetTag(Quartet));
//           if (Quartet.Tag() != Tag) continue;
//             if (Tag == HSignal && std::abs(Quartet.DeltaPhi()) < 1.5)continue;
//             if (Tag == HSignal && Quartet.Jet().m() < Mass / 2)continue;
            Quartets.push_back(Quartet);
        }




//     }

//     HJets HiggsParticles = Event.GetParticles()->GetGeneratorJets();
//     HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), WrongAbsFamily(ChargedHiggsId, GluonId)), HiggsParticles.end());
//     if (HiggsParticles.size() != 1) {
//         Print(HError, "Where is the Higgs?");
//     } else {
//         std::sort(Quartets.begin(), Quartets.end(), SortByDeltaR(HiggsParticles.front()));
//         if (Tag == HSignal && Quartets.size() > 1) Quartets.erase(Quartets.begin() + 1, Quartets.end());
//         if (Tag == HBackground && Quartets.size() > 0) Quartets.erase(Quartets.begin());
//         //         if (Jets.size() > 0) Quartets.push_back(HQuartet31(Triplet,Particles.front()));
//     }



    Print(HInformation, "Number of Heavy Higgses", Quartets.size());

    if (Tag == HSignal && Quartets.size() > 1) {
        Print(HInformation, "Higgs Candidates", Quartets.size());
        std::sort(Quartets.begin(), Quartets.end(), SortByMass(Mass));
        Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    if (Tag == HBackground && Quartets.size() > 1 && Mass > 0) {
        std::sort(Quartets.begin(), Quartets.end(), SortByMass(Mass));
        Quartets.erase(Quartets.begin());
    }


    std::vector<HChargedHiggsSemiBranch> ChargedHiggsBranches;
    for (const auto & Quartet : Quartets) ChargedHiggsBranches.push_back(GetBranch(Quartet));

    return ChargedHiggsBranches;
}


hanalysis::HObject::HTag hanalysis::HChargedHiggsSemiTagger::GetTag(const HQuartet31 &Quartet)
{
    Print(HInformation, "Get Sextet Tag");

    HJetInfo JetInfoB = Quartet.Singlet().user_info<HJetInfo>();
    JetInfoB.ExtractFraction(BottomId);
    if (std::abs(JetInfoB.MaximalId()) != BottomId) return HBackground;

    HJetInfo JetInfoB1 = Quartet.Triplet().Singlet().user_info<HJetInfo>();
    JetInfoB1.ExtractFraction(TopId);
    if (JetInfoB1.MaximalId() != TopId) return HBackground;
    if (sgn(JetInfoB.MaximalId()) != -sgn(JetInfoB1.MaximalId())) return HBackground;

    HJetInfo JetInfoW1 = Quartet.Triplet().Doublet().Singlet1().user_info<HJetInfo>();
    JetInfoW1.ExtractFraction(TopId);
    if (JetInfoB1.MaximalId() != JetInfoW1.MaximalId()) return HBackground;

//     if (Quartet.Triplet().Doublet().Singlet2().has_user_info<HJetInfo>()) {
//         HJetInfo JetInfoW2 = Quartet.Triplet().Doublet().Singlet2().user_info<HJetInfo>();
//         JetInfoW2.ExtractFraction(TopId);
//         if (JetInfoB1.MaximalId() != JetInfoW2.MaximalId()) return HBackground;
//     }

    return HSignal;
}




std::vector<hanalysis::HQuartet31>  hanalysis::HChargedHiggsSemiTagger::GetBdt(const std::vector<HTriplet> Triplets , const std::vector<fastjet::PseudoJet> Siglets, const HReader &Reader)
{

    std::vector<HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : Siglets) {
            if (Triplet.Singlet() == Jet) continue;
//             if (Triplet.Doublet().Singlet1() == Jet) continue;
//             if (Triplet.Doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Branch = GetBranch(Quartet);
            Quartet.SetBdt(Reader.Bdt());
            Quartets.push_back(Quartet);
        }

    std::sort(Quartets.begin(), Quartets.end());
    Quartets.erase(Quartets.begin() + std::min(MaxCombi, int(Quartets.size())), Quartets.end());
    return Quartets;
}
