# include "HJetPairTagger.hh"

hanalysis::HJetPairTagger::HJetPairTagger(HBottomTagger *NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    SetTaggerName("JetPair");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    Branch = new HJetPairBranch();
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

void hanalysis::HJetPairTagger::FillBranch(HJetPairBranch *const JetPairBranch, const HDoublet &Doublet)
{
    Print(HInformation, "FillPairTagger", Doublet.GetBdt());

    JetPairBranch->Mass = Doublet.GetDoubletJet().m();
    JetPairBranch->Pt = Doublet.GetDoubletJet().pt();
    JetPairBranch->Rap = Doublet.GetDoubletJet().rap();
    JetPairBranch->Phi = Doublet.GetDoubletJet().phi();
    JetPairBranch->DeltaPt = Doublet.GetDeltaPt();
    JetPairBranch->DeltaR = Doublet.GetDeltaR();
    JetPairBranch->DeltaRap = Doublet.GetDeltaRap();
    JetPairBranch->DeltaPhi = Doublet.GetPhiDelta();
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
    Observables.push_back(NewObservable(&Branch->DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));

    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

std::vector<HJetPairBranch *> hanalysis::HJetPairTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get W Tags");

    JetTag->HeavyParticles = {GluonId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    std::vector<HDoublet> Doublets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            HDoublet Doublet((*Jet1), (*Jet2));
            Doublet.SetTag(GetTag(Doublet));
            if (Doublet.GetTag() != Tag) continue;
            Doublets.push_back(Doublet);
        }

    Print(HDebug, "Number of Jet Pairs", Doublets.size());

    std::vector<HJetPairBranch *> JetPairBranches;

    if (Tag == HSignal && Doublets.size() != 1)return JetPairBranches;

    for (const auto & Doublet : Doublets) {
        HJetPairBranch *JetPairBranch = new HJetPairBranch();
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

    if (std::abs(JetInfo1.GetMaximalId()) != BottomId) return HBackground;
    if (JetInfo1.GetMaximalId() != -JetInfo2.GetMaximalId()) return HBackground;
    return HSignal;
}



std::vector<hanalysis::HDoublet>  hanalysis::HJetPairTagger::GetBdt(const HJets &Jets, const hanalysis::HReader *const JetPairReader)
{
    std::vector<HDoublet>  Doublets;
    for (auto Jet1 = Jets.begin(), JetsEnd = Jets.end(); Jet1 != JetsEnd; ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != JetsEnd; ++Jet2) {
            HDoublet Doublet(*Jet1, *Jet2);
            FillBranch(Doublet);
            Doublet.SetBdt(JetPairReader->GetBdt());
            Doublets.push_back(Doublet);
        }
    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(MaxCombi, int(Doublets.size())), Doublets.end());
    return Doublets;
}

