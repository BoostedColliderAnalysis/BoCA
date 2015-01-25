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
    Print(HInformation, "FillPairTagger", Pair.Bdt());
    FillBranch(Branch, Pair);
}

void hanalysis::HJetPairTagger::FillBranch(HEventJetPairBranch *const JetPairBranch, const HDoublet &Doublet)
{

    Print(HInformation, "FillPairTagger", Doublet.Bdt());

    JetPairBranch->Mass = Doublet.Jet().m();
    JetPairBranch->Pt = Doublet.Jet().pt();
    JetPairBranch->Rap = Doublet.Jet().rap();
    JetPairBranch->Phi = Doublet.Jet().phi();
    JetPairBranch->Ht = Doublet.Ht();

    JetPairBranch->DeltaM = Doublet.DeltaM();
    JetPairBranch->DeltaPt = Doublet.DeltaPt();
    JetPairBranch->DeltaR = Doublet.DeltaR();
    JetPairBranch->DeltaRap = Doublet.DeltaRap();
    JetPairBranch->DeltaPhi = Doublet.DeltaPhi();

    JetPairBranch->Jet1Pt = Doublet.Singlet1().pt();
    JetPairBranch->Jet1Rap = std::abs(Doublet.Singlet1().rap());
    JetPairBranch->Jet1Phi = Doublet.Singlet1().phi();
    JetPairBranch->Jet1Mass = Doublet.Singlet1().m();
    JetPairBranch->Jet1Bdt = Doublet.Singlet1().user_info<HJetInfo>().Bdt();
    JetPairBranch->Jet1BTag = Doublet.Singlet1().user_info<HJetInfo>().BTag();

    JetPairBranch->Jet2Pt = Doublet.Singlet2().pt();
    JetPairBranch->Jet2Rap = std::abs(Doublet.Singlet2().rap());
    JetPairBranch->Jet2Phi = Doublet.Singlet2().phi();
    JetPairBranch->Jet2Mass = Doublet.Singlet2().m();
    JetPairBranch->Jet2Bdt = Doublet.Singlet2().user_info<HJetInfo>().Bdt();
    JetPairBranch->Jet2BTag = Doublet.Singlet2().user_info<HJetInfo>().BTag();

    JetPairBranch->Bdt = Doublet.Bdt();
    JetPairBranch->Tag = Doublet.Tag();

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

struct SortDoubletByDeltaRap {
    inline bool operator()(const hanalysis::HDoublet &Doublet1, const hanalysis::HDoublet &Doublet2) {
        return (Doublet1.DeltaRap() > Doublet2.DeltaRap());
    }
};

std::vector<HEventJetPairBranch *> hanalysis::HJetPairTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get W Tags");

    JetTag->HeavyParticles = {GluonId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    for (const auto Jet : Jets) static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->ExtractFraction(BottomId);

    std::vector<HDoublet> Doublets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            HDoublet Doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) Doublet.SetSinglets((*Jet1), (*Jet2));
            else Doublet.SetSinglets((*Jet2), (*Jet1));
            Doublet.SetTag(GetTag(Doublet));
            if (Doublet.Tag() != Tag) continue;
            Doublets.push_back(Doublet);
        }

    Print(HDebug, "Number of Jet Pairs", Doublets.size());

    if (Tag == HSignal && Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end(), SortDoubletByDeltaRap());
        if (Doublets.size() > 1)Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    std::vector<HEventJetPairBranch *> JetPairBranches;
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

    if (std::abs(Doublet.Singlet1().user_info<HJetInfo>().MaximalId()) != BottomId) return HBackground;

    if (Doublet.Singlet1().user_info<HJetInfo>().MaximalId() != -Doublet.Singlet2().user_info<HJetInfo>().MaximalId()) return HBackground;

    return HSignal;
}



std::vector<hanalysis::HDoublet>  hanalysis::HJetPairTagger::GetBdt(const HJets &Jets, const hanalysis::HReader *const JetPairReader)
{
    std::vector<HDoublet>  Doublets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            HDoublet Doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) Doublet.SetSinglets((*Jet1), (*Jet2));
            else Doublet.SetSinglets((*Jet2), (*Jet1));
            if (std::abs(Doublet.DeltaRap()) < .5)continue;
            FillBranch(Doublet);
            Doublet.SetBdt(JetPairReader->Bdt());
            Doublets.push_back(Doublet);
        }
    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(MaxCombi, int(Doublets.size())), Doublets.end());
    return Doublets;
}

