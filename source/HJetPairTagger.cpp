# include "HJetPairTagger.hh"

hanalysis::HJetPairTagger::HJetPairTagger(HBottomTagger *NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    SetTaggerName("JetPair");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    Branch = new HEventJetPairBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HJetPairTagger::~HJetPairTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete BottomReader;
    delete JetTag;
}

void hanalysis::HJetPairTagger::FillBranch(const HDoublet &Pair)
{
    Print(HInformation, "FillPairTagger", Pair.GetBdt());
    FillBranch(Branch, Pair);
}

void hanalysis::HJetPairTagger::FillBranch(HEventJetPairBranch *const JetPairBranch, const HDoublet &Doublet)
{

    Print(HInformation, "FillPairTagger", Doublet.GetBdt());

    JetPairBranch->Mass = Doublet.GetDoubletJet().m();
    JetPairBranch->Pt = Doublet.GetDoubletJet().pt();
    JetPairBranch->Rap = Doublet.GetDoubletJet().rap();
    JetPairBranch->Phi = Doublet.GetDoubletJet().phi();
    JetPairBranch->Ht = Doublet.GetHt();

    JetPairBranch->DeltaM = Doublet.GetDeltaM();
    JetPairBranch->DeltaPt = Doublet.GetDeltaPt();
    JetPairBranch->DeltaR = Doublet.GetDeltaR();
    JetPairBranch->DeltaRap = Doublet.GetDeltaRap();
    JetPairBranch->DeltaPhi = Doublet.GetDeltaPhi();

    JetPairBranch->Jet1Pt = Doublet.GetJet1().pt();
    JetPairBranch->Jet1Rap = std::abs(Doublet.GetJet1().rap());
    JetPairBranch->Jet1Phi = Doublet.GetJet1().phi();
    JetPairBranch->Jet1Mass = Doublet.GetJet1().m();
    JetPairBranch->Jet1Bdt = Doublet.GetJet1().user_info<HJetInfo>().GetBdt();
    JetPairBranch->Jet1BTag = Doublet.GetJet1().user_info<HJetInfo>().GetBTag();

    JetPairBranch->Jet2Pt = Doublet.GetJet2().pt();
    JetPairBranch->Jet2Rap = std::abs(Doublet.GetJet2().rap());
    JetPairBranch->Jet2Phi = Doublet.GetJet2().phi();
    JetPairBranch->Jet2Mass = Doublet.GetJet2().m();
    JetPairBranch->Jet2Bdt = Doublet.GetJet2().user_info<HJetInfo>().GetBdt();
    JetPairBranch->Jet2BTag = Doublet.GetJet2().user_info<HJetInfo>().GetBTag();

    JetPairBranch->Bdt = Doublet.GetBdt();
    JetPairBranch->Tag = Doublet.GetTag();

}

void hanalysis::HJetPairTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch->Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch->DeltaM, "DeltaM"));
    Observables.push_back(NewObservable(&Branch->DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch->Jet1Mass, "Jet1Mass"));
    Observables.push_back(NewObservable(&Branch->Jet1Pt, "Jet1Pt"));
    Observables.push_back(NewObservable(&Branch->Jet1Rap, "Jet1Rap"));
    Observables.push_back(NewObservable(&Branch->Jet1Phi, "Jet1Phi"));
    Observables.push_back(NewObservable(&Branch->Jet1Bdt, "Jet1Bdt"));
    Observables.push_back(NewObservable(&Branch->Jet1BTag, "Jet1BTag"));

    Observables.push_back(NewObservable(&Branch->Jet2Mass, "Jet2Mass"));
    Observables.push_back(NewObservable(&Branch->Jet2Pt, "Jet2Pt"));
    Observables.push_back(NewObservable(&Branch->Jet2Rap, "Jet2Rap"));
    Observables.push_back(NewObservable(&Branch->Jet2Phi, "Jet2Phi"));
    Observables.push_back(NewObservable(&Branch->Jet2Bdt, "Jet2Bdt"));
    Observables.push_back(NewObservable(&Branch->Jet2BTag, "Jet2BTag"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

struct SortDoubletByPt {
    inline bool operator()(const hanalysis::HDoublet &Doublet1, const hanalysis::HDoublet &Doublet2) {
        return (Doublet1.GetDoubletJet().pt() > Doublet2.GetDoubletJet().pt());
    }
};

std::vector<HEventJetPairBranch *> hanalysis::HJetPairTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get W Tags");

    JetTag->HeavyParticles = {GluonId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
//     for(const auto Jet :Jets) Print(HError,"B Tag",Jet.user_info<HJetInfo>().GetBTag());
    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    std::vector<HDoublet> Doublets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            HDoublet Doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) Doublet.SetJets((*Jet1), (*Jet2));
            else Doublet.SetJets((*Jet2), (*Jet1));
            Doublet.SetTag(GetTag(Doublet));
            if (Doublet.GetTag() != Tag) continue;
            Doublets.push_back(Doublet);
        }

    std::vector<HEventJetPairBranch *> JetPairBranches;

    Print(HDebug, "Number of Jet Pairs", Doublets.size());

    if (Tag == HSignal && Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end(), SortDoubletByPt());
        if (Doublets.size() > 1)Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) {
        HEventJetPairBranch *JetPairBranch = new HEventJetPairBranch();
        FillBranch(JetPairBranch, Doublet);
        JetPairBranches.push_back(JetPairBranch);
    }

    return JetPairBranches;

}

hanalysis::HObject::HTag hanalysis::HJetPairTagger::GetTag(const HDoublet &Doublet)
{
    Print(HInformation, "Get Doublet Tag");

    HJetInfo JetInfo1 = Doublet.GetJet1().user_info<HJetInfo>();
//     JetInfo1.PrintAllFamilyInfos(HError);
    JetInfo1.ExtractFraction(BottomId);
//     JetInfo1.PrintAllInfos(HError);
    HJetInfo JetInfo2 = Doublet.GetJet2().user_info<HJetInfo>();
//     JetInfo2.PrintAllFamilyInfos(HError);
    JetInfo2.ExtractFraction(BottomId);
//     JetInfo2.PrintAllInfos(HError);

    Print(HDebug, "Pair is", JetInfo1.GetMaximalId(), JetInfo2.GetMaximalId(), Doublet.GetJet1().pt(), Doublet.GetJet2().pt());

    if (std::abs(JetInfo1.GetMaximalId()) != BottomId) return HBackground;
    if (JetInfo1.GetMaximalId() != -JetInfo2.GetMaximalId()) return HBackground;
    return HSignal;
}



std::vector<hanalysis::HDoublet>  hanalysis::HJetPairTagger::GetBdt(const HJets &Jets, const hanalysis::HReader *const JetPairReader)
{
    std::vector<HDoublet>  Doublets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
          HDoublet Doublet;
          if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) Doublet.SetJets((*Jet1), (*Jet2));
          else Doublet.SetJets((*Jet2), (*Jet1));
            FillBranch(Doublet);
            Doublet.SetBdt(JetPairReader->GetBdt());
            Doublets.push_back(Doublet);
        }
    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(MaxCombi, int(Doublets.size())), Doublets.end());
    return Doublets;
}

