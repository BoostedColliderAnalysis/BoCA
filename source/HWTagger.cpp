# include "HWTagger.hh"

hanalysis::HWTagger::HWTagger(HBottomTagger *NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    SetTaggerName("W");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    Branch = new HWBranch();
    JetTag = new HJetTag();

    DefineVariables();
    float WMassWindow = 20;
    std::string WCut = "W.Mass>" + std::to_string(WMass - WMassWindow) + "&&W.Mass<" + std::to_string(WMass + WMassWindow);
    Cut = WCut.c_str();
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
    Print(HInformation, "FillPairTagger", Pair.GetBdt());
    FillBranch(Branch, Pair);
}

void hanalysis::HWTagger::FillBranch(HWBranch *const WBranch, const HDoublet &Doublet)
{
    Print(HInformation, "FillPairTagger", Doublet.GetBdt());

    WBranch->Mass = Doublet.GetDoubletJet().m();
    WBranch->Pt = Doublet.GetDoubletJet().pt();
    WBranch->Rap = Doublet.GetDoubletJet().rap();
    WBranch->Phi = Doublet.GetDoubletJet().phi();
    WBranch->DeltaPt = Doublet.GetDeltaPt();
    WBranch->DeltaR = Doublet.GetDeltaR();
    WBranch->DeltaRap = Doublet.GetDeltaRap();
    WBranch->DeltaPhi = Doublet.GetDeltaPhi();
    WBranch->Bdt = Doublet.GetBdt();
    WBranch->Tag = Doublet.GetTag();

}

void hanalysis::HWTagger::DefineVariables()
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



struct SortByWMass {
    inline bool operator()(const hanalysis::HDoublet &Doublet1, const hanalysis::HDoublet &Doublet2) {
        hanalysis::HObject Object;
        return (std::abs(Doublet1.WMass - Doublet1.GetDoubletJet().m()) < std::abs(Doublet2.WMass - Doublet2.GetDoubletJet().m()));
    }
};

std::vector<HWBranch *> hanalysis::HWTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get W Tags");

    JetTag->HeavyParticles = {WId};
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

    if (Tag == HSignal && Doublets.size() < 1 || Tag == HBackground) {
        for (auto & Jet : Jets) {
            if (Jet.has_pieces()) {
                HTag JetTag = GetTag(Jet);
                if (JetTag != Tag) continue;
                fastjet::JetDefinition JetDefinition(fastjet::cambridge_aachen_algorithm, .49);
                fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
                std::vector<fastjet::PseudoJet> Pieces = fastjet::sorted_by_pt(ClusterSequence.inclusive_jets());
                Print(HInformation, "New Jet Number", Pieces.size());
                if (Pieces.size() > 1) {
                    for (auto & Piece : Pieces) {
                        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                        JetInfo->SetBdt(Jet.user_info<HJetInfo>().GetBdt());
                        JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
                        JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
                        Piece.set_user_info(JetInfo);
                    }
                    HDoublet Doublet(Pieces.at(0), Pieces.at(1));
                    Doublet.SetTag(JetTag);
                    Doublets.push_back(Doublet);
                }
            }
        }
    }

    if (Tag == HSignal && Doublets.size() > 1) { // FIXME assuming maximal one hadronic W
        Print(HError, "Number of Jet Pairs", Doublets.size());
        std::sort(Doublets.begin(), Doublets.end(), SortByWMass());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
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

    HJetInfo JetInfo1 = Doublet.GetJet1().user_info<HJetInfo>();
    JetInfo1.PrintAllFamilyInfos(HDebug);
    JetInfo1.ExtractFraction(WId);
    JetInfo1.PrintAllInfos(HDebug);
    HJetInfo JetInfo2 = Doublet.GetJet2().user_info<HJetInfo>();
    JetInfo2.ExtractFraction(WId);
    JetInfo2.PrintAllInfos(HDebug);

//     if (Doublet.GetJet1().user_index() != Doublet.GetJet2().user_index()) return HBackground;
    if (std::abs(JetInfo1.GetMaximalId()) != WId) return HBackground;
    if (JetInfo1.GetMaximalId() != JetInfo2.GetMaximalId()) return HBackground;
    return HSignal;
}

hanalysis::HObject::HTag hanalysis::HWTagger::GetTag(const fastjet::PseudoJet &Singlet)
{
    Print(HInformation, "Get Singlet Tag");

    HJetInfo JetInfo1 = Singlet.user_info<HJetInfo>();
    JetInfo1.ExtractFraction(WId);

    if (std::abs(JetInfo1.GetMaximalId()) != WId) return HBackground;
    return HSignal;
}


std::vector<hanalysis::HDoublet>  hanalysis::HWTagger::GetBdt(HJets &Jets, const hanalysis::HReader *const WReader)
{
    std::vector<HDoublet>  Doublets;
    for (auto Jet1 = Jets.begin(), JetsEnd = Jets.end(); Jet1 != JetsEnd; ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != JetsEnd; ++Jet2) {
            HDoublet Doublet(*Jet1, *Jet2);
            FillBranch(Doublet);
            Doublet.SetBdt(WReader->GetBdt());
            Doublets.push_back(Doublet);
        }

    for (auto & Jet : Jets) {
        if (Jet.has_pieces()) {
            fastjet::JetDefinition JetDefinition(fastjet::cambridge_aachen_algorithm, .49);
            fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
            std::vector<fastjet::PseudoJet> Pieces = fastjet::sorted_by_pt(ClusterSequence.inclusive_jets());
            if (Pieces.size() > 1) {
                for (auto & Piece : Pieces) {
                    hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                    JetInfo->SetBdt(Jet.user_info<HJetInfo>().GetBdt());
                    JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
                    JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
                    Piece.set_user_info(JetInfo);
                    Print(HError,"Info",Piece.user_info<HJetInfo>().ExtractFraction(BottomId));//FIXME work to do
                    Piece.user_info<HJetInfo>().PrintAllInfos(HError);
                }
                HDoublet Doublet(Pieces.at(0), Pieces.at(1));
                FillBranch(Doublet);
                Doublet.SetBdt(WReader->GetBdt());
                Doublets.push_back(Doublet);
            }
        }
    }

    std::sort(Doublets.begin(), Doublets.end(), SortByWMass());
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
        for (const auto & Constituent : JetPair.GetConstituents()) {
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

