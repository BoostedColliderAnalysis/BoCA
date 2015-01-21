# include "HTopLeptonicTagger.hh"

hanalysis::HTopLeptonicTagger::HTopLeptonicTagger(HBottomTagger *const NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    SetTaggerName("TopLeptonic");
    Branch = new HTopLeptonicBranch();
    JetTag = new HJetTag();
    DefineVariables();
}

hanalysis::HTopLeptonicTagger::~HTopLeptonicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
}

void hanalysis::HTopLeptonicTagger::FillBranch(const HDoublet &Doublet)
{
    Print(HInformation, "Fill Top Tagger", Doublet.Bdt());
    FillBranch(Branch, Doublet);
}

void hanalysis::HTopLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));

    Observables.push_back(NewObservable(&Branch->BottomPt, "BottomPt"));
    Observables.push_back(NewObservable(&Branch->LeptonPt, "LeptonPt"));

    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HTopLeptonicTagger::FillBranch(HTopLeptonicBranch *const TopLeptonicBranch, const hanalysis::HDoublet &Doublet)
{
    Print(HInformation, "Fill Top Tagger", Doublet.Bdt());

    TopLeptonicBranch->Mass = Doublet.Jet().m();
    TopLeptonicBranch->Pt = Doublet.Jet().pt();
    TopLeptonicBranch->Rap = Doublet.Jet().rap();
    TopLeptonicBranch->Phi = Doublet.Jet().phi();

    TopLeptonicBranch->BottomPt = Doublet.Singlet1().pt();
    TopLeptonicBranch->LeptonPt = Doublet.Singlet2().pt();

    TopLeptonicBranch->DeltaR = Doublet.DeltaR();
    TopLeptonicBranch->DeltaRap = Doublet.DeltaRap();
    TopLeptonicBranch->DeltaPhi = Doublet.DeltaPhi();

    TopLeptonicBranch->Bdt = Doublet.Bdt();
    TopLeptonicBranch->Tag = Doublet.Tag();

}

// struct SortByTopMass {
//     inline bool operator()(const hanalysis::HDoublet &Doublet1, const hanalysis::HDoublet &Doublet2) {
//         return (std::abs(Doublet1.Jet().m() - Doublet1.TopMass) < std::abs(Doublet2.Jet().m() - Doublet2.TopMass));
//     }
// };

std::vector<HTopLeptonicBranch *> hanalysis::HTopLeptonicTagger::GetBranches(HEvent *const Event, const HObject::HTag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Jets = BottomTagger->GetBdt(Jets, BottomReader);
    Print(HInformation, "Jet Number", Jets.size());

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons)
        for (const auto & Jet : Jets) {
            HDoublet Doublet(Jet, Lepton);
            Doublet.SetTag(GetTag(Doublet));
            if (Doublet.Tag() != Tag) continue;
            if (Tag == HSignal && Doublet.Jet().m() > TopMass) continue;
            Doublets.push_back(Doublet);
        }


    Print(HInformation, "Number JetPairs", Doublets.size());

    if (Tag == HSignal && Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end(), SortByMass<HDoublet>(TopMass));
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    std::vector<HTopLeptonicBranch *> TopLeptonicBranches;
    for (const auto & Doublet : Doublets) {
        HTopLeptonicBranch *TopLeptonicBranch = new HTopLeptonicBranch();
        FillBranch(TopLeptonicBranch, Doublet);
        TopLeptonicBranches.push_back(TopLeptonicBranch);
    }

    return TopLeptonicBranches;

}

hanalysis::HObject::HTag hanalysis::HTopLeptonicTagger::GetTag(const HDoublet &Doublet)
{
    Print(HInformation, "Get Triple Tag", GetParticleName(Doublet.Singlet1().user_index()), GetParticleName(Doublet.Singlet2().user_index()));

    HJetInfo BJetInfo = Doublet.Singlet1().user_info<HJetInfo>();
    BJetInfo.ExtractFraction(BottomId);
    HJetInfo LJetInfo = Doublet.Singlet2().user_info<HJetInfo>();
    LJetInfo.ExtractFraction(WId);

    if (std::abs(LJetInfo.GetMaximalId()) != WId) return HBackground;
    if (std::abs(BJetInfo.GetMaximalId()) != BottomId) return HBackground;
    if (sgn(BJetInfo.GetMaximalId()) != sgn(LJetInfo.GetMaximalId())) return HBackground;

    return HSignal;
}

std::vector<hanalysis::HDoublet>  hanalysis::HTopLeptonicTagger::GetBdt(const HJets &Jets, HJets &Leptons, const hanalysis::HReader *const Reader)
{

    Print(HInformation, "Get Bdt");
    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        for (const auto & Jet : Jets) {
            HDoublet Doublet(Jet, Lepton);
            FillBranch(Doublet);
            Doublet.SetBdt(Reader->Bdt());
            Doublets.push_back(Doublet);
        }
    }

    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(MaxCombi, int(Doublets.size())), Doublets.end());

    return Doublets;

}
