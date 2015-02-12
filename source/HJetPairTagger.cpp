# include "HJetPairTagger.hh"

hanalysis::HJetPairTagger::HJetPairTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    SetTaggerName("JetPair");
    DefineVariables();
}

hanalysis::HJetPairTagger::~HJetPairTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HJetPairTagger::SetTagger(const HBottomTagger &NewBottomTagger)
{
    Print(HNotification, "Set Tagger", NewBottomTagger.GetTaggerName());
    BottomTagger = NewBottomTagger;
//     BottomTagger.SetTagger();
//     BottomReader.SetMva(BottomTagger);

    SetTaggerName("JetPair");
    DefineVariables();
}

void hanalysis::HJetPairTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.DeltaM, "DeltaM"));
    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch.Jet1Mass, "Jet1Mass"));
    Observables.push_back(NewObservable(&Branch.Jet1Pt, "Jet1Pt"));
    Observables.push_back(NewObservable(&Branch.Jet1Rap, "Jet1Rap"));
    Observables.push_back(NewObservable(&Branch.Jet1Phi, "Jet1Phi"));
    Observables.push_back(NewObservable(&Branch.Jet1Bdt, "Jet1Bdt"));
//     Observables.push_back(NewObservable(&Branch.Jet1BTag, "Jet1BTag"));

    Observables.push_back(NewObservable(&Branch.Jet2Mass, "Jet2Mass"));
    Observables.push_back(NewObservable(&Branch.Jet2Pt, "Jet2Pt"));
    Observables.push_back(NewObservable(&Branch.Jet2Rap, "Jet2Rap"));
    Observables.push_back(NewObservable(&Branch.Jet2Phi, "Jet2Phi"));
    Observables.push_back(NewObservable(&Branch.Jet2Bdt, "Jet2Bdt"));
//     Observables.push_back(NewObservable(&Branch.Jet2BTag, "Jet2BTag"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

HEventJetPairBranch hanalysis::HJetPairTagger::GetBranch(const HDoublet &Doublet) const
{

    Print(HInformation, "FillPairTagger", Doublet.Bdt());

    HEventJetPairBranch JetPairBranch;

    JetPairBranch.Mass = Doublet.Jet().m();
    JetPairBranch.Pt = Doublet.Jet().pt();
    JetPairBranch.Rap = Doublet.Jet().rap();
    JetPairBranch.Phi = Doublet.Jet().phi();
    JetPairBranch.Ht = Doublet.Ht();

    JetPairBranch.DeltaM = Doublet.DeltaM();
    JetPairBranch.DeltaPt = Doublet.DeltaPt();
    JetPairBranch.DeltaR = Doublet.DeltaR();
    JetPairBranch.DeltaRap = Doublet.DeltaRap();
    JetPairBranch.DeltaPhi = Doublet.DeltaPhi();

    JetPairBranch.Jet1Pt = Doublet.Singlet1().pt();
    JetPairBranch.Jet1Rap = std::abs(Doublet.Singlet1().rap());
    JetPairBranch.Jet1Phi = Doublet.Singlet1().phi();
    JetPairBranch.Jet1Mass = Doublet.Singlet1().m();
    JetPairBranch.Jet1Bdt = Doublet.Singlet1().user_info<HJetInfo>().Bdt();
//     JetPairBranch.Jet1BTag = Doublet.Singlet1().user_info<HJetInfo>().BTag();

    JetPairBranch.Jet2Pt = Doublet.Singlet2().pt();
    JetPairBranch.Jet2Rap = std::abs(Doublet.Singlet2().rap());
    JetPairBranch.Jet2Phi = Doublet.Singlet2().phi();
    JetPairBranch.Jet2Mass = Doublet.Singlet2().m();
    JetPairBranch.Jet2Bdt = Doublet.Singlet2().user_info<HJetInfo>().Bdt();
//     JetPairBranch.Jet2BTag = Doublet.Singlet2().user_info<HJetInfo>().BTag();

    JetPairBranch.Bdt = Doublet.Bdt();
    JetPairBranch.Tag = Doublet.Tag();

//     Print(HError, "Mass", JetPairBranch.Mass);
//     Print(HError, "Pt", JetPairBranch.Pt);
//     Print(HError, "Rap", JetPairBranch.Rap);
//     Print(HError, "Phi", JetPairBranch.Phi);
//     Print(HError, "Ht", JetPairBranch.Ht);
//
//     Print(HError, "DeltaPt", JetPairBranch.DeltaPt);
//     Print(HError, "DeltaM", JetPairBranch.DeltaM);
//     Print(HError, "DeltaR", JetPairBranch.DeltaR);
//     Print(HError, "DeltaRap", JetPairBranch.DeltaRap);
//
//     Print(HError, "Jet1Pt", JetPairBranch.Jet1Pt);
//     Print(HError, "Jet1Rap", JetPairBranch.Jet1Rap);
//     Print(HError, "Jet1Phi", JetPairBranch.Jet1Phi);
//     Print(HError, "Jet1Bdt", JetPairBranch.Jet1Bdt);
//     Print(HError, "Jet1Mass", JetPairBranch.Jet1Mass);
//     Print(HError, "Jet1BTag", JetPairBranch.Jet1BTag);
//
//     Print(HError, "Jet2Pt", JetPairBranch.Jet2Pt);
//     Print(HError, "Jet2Rap", JetPairBranch.Jet2Rap);
//     Print(HError, "Jet2Phi", JetPairBranch.Jet2Phi);
//     Print(HError, "Jet2Bdt", JetPairBranch.Jet2Bdt);
//     Print(HError, "Jet2Mass", JetPairBranch.Jet2Mass);
//     Print(HError, "Jet2BTag", JetPairBranch.Jet2BTag);
    return JetPairBranch;
}

std::vector<HEventJetPairBranch> hanalysis::HJetPairTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Jet Pair Tags");
    JetTag.HeavyParticles = {GluonId};
    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);


    HJets Particles = Event.GetParticles()->Generator();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsFamily(BottomId, GluonId)), Particles.end());
    if (Particles.size() != 2) Print(HError, "Where are the Bottoms?", Particles.size());
    HJets BottomJets;
    for (const auto & Particle : Particles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
        if (Tag == HSignal) BottomJets.push_back(Jets.front());
        if (Jets.size() > 1) Jets.erase(Jets.begin());
    }
    if (Tag == HBackground) BottomJets = Jets;

    std::vector<HDoublet> Doublets;
    for (auto Jet1 = BottomJets.begin(); Jet1 != BottomJets.end(); ++Jet1)
      for (auto Jet2 = Jet1 + 1; Jet2 != BottomJets.end(); ++Jet2) {
            HDoublet Doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) Doublet.SetSinglets((*Jet1), (*Jet2));
            else Doublet.SetSinglets((*Jet2), (*Jet1));
//             Doublet.SetTag(GetTag(Doublet));
//             if (Doublet.Tag() != Tag) continue;
            Doublets.push_back(Doublet);
        }

    Print(HDebug, "Number of Jet Pairs", Doublets.size());

    if (Tag == HSignal && Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end(), MaxDeltaRap());
        if (Doublets.size() > 1)Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    std::vector<HEventJetPairBranch> JetPairBranches;
    for (const auto & Doublet : Doublets) JetPairBranches.push_back(GetBranch(Doublet));

    return JetPairBranches;

}

hanalysis::HObject::HTag hanalysis::HJetPairTagger::GetTag(const HDoublet &Doublet)
{
    Print(HInformation, "Get Doublet Tag");

    if (std::abs(Doublet.Singlet1().user_info<HJetInfo>().MaximalId()) != BottomId) return HBackground;

    if (Doublet.Singlet1().user_info<HJetInfo>().MaximalId() != -Doublet.Singlet2().user_info<HJetInfo>().MaximalId()) return HBackground;

    return HSignal;
}



std::vector<hanalysis::HDoublet>  hanalysis::HJetPairTagger::GetBdt(const HJets &Jets, const hanalysis::HReader &JetPairReader)
{
    std::vector<HDoublet>  Doublets;
//     int Counter = 0;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
//             ++Counter;
            HDoublet Doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) Doublet.SetSinglets((*Jet1), (*Jet2));
            else Doublet.SetSinglets((*Jet2), (*Jet1));
            if (std::abs(Doublet.DeltaRap()) < .5)continue;
//             Print(HError, "Counter", Counter);
            Branch = GetBranch(Doublet);
            Doublet.SetBdt(JetPairReader.Bdt());
            Doublets.push_back(Doublet);
        }
    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(MaxCombi, int(Doublets.size())), Doublets.end());
    return Doublets;
}

