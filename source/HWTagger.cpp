# include "HWTagger.hh"

hanalysis::HWTagger::HWTagger(HBottomTagger *NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    SetTaggerName("WHadronic");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    Branch = new HWBranch();
    JetTag = new HJetTag();

    DefineVariables();
    WMassWindow = 20;
    JetRadiusParameter = 1;
}

hanalysis::HWTagger::~HWTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete BottomReader;
    delete JetTag;
}

void hanalysis::HWTagger::FillBranch(const HDoublet &Pair)
{
    Print(HInformation, "FillPairTagger", Pair.Bdt());
    FillBranch(Branch, Pair);
}

void hanalysis::HWTagger::FillBranch(HWBranch *const WBranch, const HDoublet &Doublet)
{
    Print(HInformation, "FillPairTagger", Doublet.Bdt());

    WBranch->Mass = Doublet.Jet().m();
    WBranch->Rap = Doublet.Jet().rap();
    WBranch->Phi = Doublet.Jet().phi();
    WBranch->Pt = Doublet.Jet().pt();
    WBranch->Ht = Doublet.Ht();
    WBranch->DeltaPt = std::abs(Doublet.DeltaPt());
    WBranch->DeltaR = Doublet.DeltaR();
    WBranch->DeltaRap = std::abs(Doublet.DeltaRap());
    WBranch->DeltaPhi = std::abs(Doublet.DeltaPhi());
    WBranch->Bdt = Doublet.Bdt();
    WBranch->Tag = Doublet.Tag();

}

void hanalysis::HWTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Ht, "Ht"));
    Observables.push_back(NewObservable(&Branch->DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));

    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}


std::vector<HWBranch *> hanalysis::HWTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get W Tags");

    JetTag->HeavyParticles = {WId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jets Number", Jets.size());

    Jets = BottomTagger->GetBdt(Jets, BottomReader);
    Print(HInformation, "Bottom Tagger Number", Jets.size());

    for (const auto & Jet : Jets) static_cast<hanalysis::HJetInfo *>(Jet.user_info_shared_ptr().get())->ExtractFraction(WId);

    std::vector<HDoublet> Doublets;

    // combine 2 jets to one W
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            HDoublet Doublet((*Jet1), (*Jet2));
            Doublet.SetTag(GetTag(Doublet));
            if (Doublet.Tag() != Tag) continue;
            if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
            Doublets.push_back(Doublet);
        }

    // choose single jets
    for (const auto & Jet : Jets) {
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Jet without Jet Info");
            continue;
        }
        static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(GetTag(Jet));
        if (Jet.user_info<HJetInfo>().Tag() != Tag) continue;
        if (Tag == HSignal && std::abs(Jet.m() - WMass) > WMassWindow) continue;
        HDoublet Doublet(Jet);
        Doublets.push_back(Doublet);
    }

    if (Tag == HSignal && Doublets.size() > 1) {
        Print(HInformation, "Number of Jet Pairs", Doublets.size());
        std::sort(Doublets.begin(), Doublets.end(), SortByMass<HDoublet>(WMass));
        Doublets.erase(Doublets.begin() + 1, Doublets.end()); // FIXME assuming maximal one hadronic W
    }

    std::vector<HWBranch *> WBranches;
    for (const auto & Doublet : Doublets) {
        HWBranch *WBranch = new HWBranch();
        FillBranch(WBranch, Doublet);
        WBranches.push_back(WBranch);
    }

    return WBranches;

}


hanalysis::HObject::HTag hanalysis::HWTagger::GetTag(const HDoublet &Doublet)
{
    Print(HInformation, "Get Doublet Tag");

    if (std::abs(Doublet.Singlet1().user_info<HJetInfo>().MaximalId()) != WId) return HBackground;

    if (Doublet.Singlet1().user_info<HJetInfo>().MaximalId() != Doublet.Singlet2().user_info<HJetInfo>().MaximalId()) return HBackground;

    return HSignal;
}

hanalysis::HObject::HTag hanalysis::HWTagger::GetTag(const fastjet::PseudoJet &Singlet)
{
    Print(HInformation, "Get Singlet Tag");

    if (std::abs(Singlet.user_info<HJetInfo>().MaximalId()) != WId) return HBackground;
    return HSignal;
}


std::vector<hanalysis::HDoublet>  hanalysis::HWTagger::GetBdt(const HJets &Jets, const hanalysis::HReader *const WReader)
{
    Print(HInformation, "Get Doublet Bdt");

    std::vector<HDoublet>  Doublets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            HDoublet Doublet(*Jet1, *Jet2);
            if (Doublet.DeltaR() < MinCellResolution) continue;
            if (std::abs(Doublet.Jet().rap()) > 100) continue;
            if (std::abs(Doublet.Jet().m()) < 10) continue;
            FillBranch(Doublet);
            Doublet.SetBdt(WReader->Bdt());
            Doublets.push_back(Doublet);
        }

    for (auto & Jet : Jets) {
        HDoublet Doublet(Jet);
        if (std::abs(Doublet.Jet().rap()) > 100) continue;
        if (std::abs(Doublet.Jet().m()) < 10) continue;
        FillBranch(Doublet);
        Doublet.SetBdt(WReader->Bdt());
        Doublets.push_back(Doublet);
    }

    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(MaxCombi, int(Doublets.size())), Doublets.end());
    return Doublets;
}

std::vector<HParticleBranch *> hanalysis::HWTagger::GetConstituentBranches()
{

    Print(HInformation, "Get Higgs Tags");

    std::vector<HDoublet> JetPairs;

    Print(HInformation, "Number of Jet Pairs", JetPairs.size());

    std::vector<HParticleBranch *> ConstituentBranches;
    for (const auto & JetPair : JetPairs) {
        for (const auto & Constituent : JetPair.Constituents()) {
            HParticleBranch *ConstituentBranch = new HParticleBranch();
            FillBranch(ConstituentBranch, Constituent);
            ConstituentBranches.push_back(ConstituentBranch);
        }
    }

    return ConstituentBranches;

}

void hanalysis::HWTagger::FillBranch(const HKinematics &Vector)
{
    Print(HInformation, "FillPairTagger", Vector.GetPt());

    FillBranch(Vector);

}

void hanalysis::HWTagger::FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector)
{
    Print(HInformation, "Fill Constituent Branch");

    ConstituentBranch->Pt = Vector.GetPt();
    ConstituentBranch->Rap = Vector.GetRap();
    ConstituentBranch->Phi = Vector.GetPhi();

}

