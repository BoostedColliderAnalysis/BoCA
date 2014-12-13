# include "HHeavyHiggsLeptonicTagger.hh"

hanalysis::HHeavyHiggsLeptonicTagger::HHeavyHiggsLeptonicTagger(HBottomTagger* const NewBottomTagger, HTopLeptonicTagger* const NewTopLeptonicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    TopLeptonicTagger = NewTopLeptonicTagger;
    TopLeptonicReader = new HReader(TopLeptonicTagger);

    TaggerName = "HeavyHiggsLeptonic";
    SignalNames = {"HeavyHiggsLeptonic"};
    BackgroundNames = {"NotHeavyHiggsLeptonic"};
    CandidateBranchName = "HeavyHiggsLeptonic";

    Branch = new HHeavyHiggsLeptonicBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HHeavyHiggsLeptonicTagger::~HHeavyHiggsLeptonicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopLeptonicReader;

}

void hanalysis::HHeavyHiggsLeptonicTagger::FillBranch(HHeavyHiggsLeptonicBranch* HeavyHiggsBranch, const HSextet& Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.GetBdt());

    HeavyHiggsBranch->HeavyHiggsMass = Sextet.GetSextetJet().m();
    HeavyHiggsBranch->HeavyHiggsPt = Sextet.GetSextetJet().m();

    HeavyHiggsBranch->TopDeltaR = Sextet.GetDeltaR();
    HeavyHiggsBranch->TopDeltaRap = Sextet.GetDeltaRap();
    HeavyHiggsBranch->TopDeltaPhi = Sextet.GetDeltaPhi();

    HeavyHiggsBranch->LargerWDeltaR = Sextet.GetLargerTripletDeltaR();
    HeavyHiggsBranch->LargerWDeltaRap = Sextet.GetLargerTripletDeltaRap();
    HeavyHiggsBranch->LargerWDeltaPhi = Sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch->SmallerWDeltaR = Sextet.GetSmallerTripletDeltaR();
    HeavyHiggsBranch->SmallerWDeltaRap = Sextet.GetSmallerTripletDeltaRap();
    HeavyHiggsBranch->SmallerWDeltaPhi = Sextet.GetSmallerTripletDeltaPhi();

    HeavyHiggsBranch->LargerNeutrinoDeltaR = Sextet.GetLargerTripletDeltaR();
    HeavyHiggsBranch->LargerNeutrinoDeltaRap = Sextet.GetLargerTripletDeltaRap();
    HeavyHiggsBranch->LargerNeutrinoDeltaPhi = Sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch->SmallerNeutrinoDeltaR = Sextet.GetSmallerTripletDeltaR();
    HeavyHiggsBranch->SmallerNeutrinoDeltaRap = Sextet.GetSmallerTripletDeltaRap();
    HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = Sextet.GetSmallerTripletDeltaPhi();

    HeavyHiggsBranch->TopBdt = Sextet.GetBdt();
    HeavyHiggsBranch->HeavyHiggsTag = Sextet.GetTag();

}

void hanalysis::HHeavyHiggsLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch->TopDeltaR, "TopDeltaR"));
    Observables.push_back(NewObservable(&Branch->TopDeltaRap, "TopDeltaRap"));
    Observables.push_back(NewObservable(&Branch->TopDeltaPhi, "TopDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->LargerWDeltaR, "LargerWDeltaR"));
    Observables.push_back(NewObservable(&Branch->LargerWDeltaRap, "LargerWDeltaRap"));
    Observables.push_back(NewObservable(&Branch->LargerWDeltaPhi, "LargerWDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->SmallerWDeltaR, "SmallerWDeltaR"));
    Observables.push_back(NewObservable(&Branch->SmallerWDeltaRap, "SmallerWDeltaRap"));
    Observables.push_back(NewObservable(&Branch->SmallerWDeltaPhi, "SmallerWDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR"));
    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap"));
    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR"));
    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap"));
    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->TopBdt, "TopBdt"));

    Spectators.push_back(NewObservable(&Branch->HeavyHiggsTag, "HeavyHiggsTag"));
    Spectators.push_back(NewObservable(&Branch->HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}

struct SortPairByMass {
    inline bool operator()(const hanalysis::HQuartet& Pair1, const hanalysis::HQuartet& Pair2) {
        return (Pair1.GetMassDifference(400) > Pair2.GetMassDifference(400));
    }
};

struct SortByError {
    inline bool operator()(const hanalysis::HSextet& Pair1, const hanalysis::HSextet& Pair2) {
        return (Pair1.GetError() < Pair2.GetError());
    }
};

std::vector< HHeavyHiggsLeptonicBranch* > hanalysis::HHeavyHiggsLeptonicTagger::GetBranches(HEvent* const Event, const HObject::HState State)
{
    Print(HInformation, "Get Higgs Tags");

    std::vector<HHeavyHiggsLeptonicBranch*> HeavyHiggsBranches;

    JetTag->HeavyParticles = {TopId, HeavyHiggsId, WId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    if (Jets.size() < 2) return HeavyHiggsBranches;

    Jets = BottomTagger->GetBottomBdt(Jets,BottomReader);

//     for (auto Jet = Jets.begin(); Jet != Jets.end();) {
//         if (std::abs((*Jet).user_index()) == MixedJetId) {
//             Jet = Jets.erase(Jet);
//         } else {
//             HJetInfo* JetInfo = new HJetInfo;
//             BottomTagger->FillBranch(*Jet);
//             JetInfo->SetBdt(BottomReader->GetBdt());
//             (*Jet).set_user_info(JetInfo);
//             ++Jet;
//         }
//     }


//     HJets HeavyHiggsJets;
//     HJets OtherJets;
//     for (auto & Jet : Jets) {
//         Print(HInformation, "Jet Id", GetParticleName(Jet.user_info<HJetInfo>().GetMaximalId()));
//
//         if (std::abs(Jet.user_index()) == MixedJetId) continue;
//         HJetInfo *JetInfo = new HJetInfo;
//         BottomTagger->FillBranch(Jet);
//         JetInfo->SetBdt(BottomReader->GetBdt());
//         Jet.set_user_info(JetInfo);
//         Print(HDebug, "User index", Jet.user_index());
//         if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(JetId))) != end(JetTag->HeavyParticles)) HeavyHiggsJets.push_back(Jet);
//         else OtherJets.push_back(Jet);
//
//     }
//     Print(HDebug, "Jets", Jets.size(), HeavyHiggsJets.size(), OtherJets.size());
//     if (State == HSignal && HeavyHiggsJets.size() < 2)  {
//         Print(HInformation, "Not enough Higgsjets", HeavyHiggsJets.size());
//         return HeavyHiggsBranches;
//     }

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
//     if (Leptons.size() < 2) {
//         return HeavyHiggsBranches;
//     }

    std::vector<HDoublet> Doublets=TopLeptonicTagger->GetTopLeptonicBdt(Jets,Leptons,TopLeptonicReader,State);

//     for (auto Lepton = Leptons.begin(); Lepton != Leptons.end();) {
//         if (std::abs((*Lepton).user_index()) == MixedJetId) {
//             Lepton = Leptons.erase(Lepton);
//         } else {
//             ++Lepton;
//         }
//     }
//
//     std::vector<HDoublet> Doublets;
//     for (const auto & Lepton : Leptons){
//         if (State == HSignal && std::abs(Lepton.user_index()) != WId) continue;
//         for (const auto & Jet : Jets) {
//             if (State == HSignal && std::abs(Jet.user_index()) != TopId) continue;
//             if (State == HSignal && sgn(Lepton.user_index()) != sgn(Jet.user_index())) continue;
//             HDoublet Doublet(Jet, Lepton);
//             TopLeptonicTagger->FillBranch(Doublet);
//             Doublet.SetBdt(TopLeptonicReader->GetBdt());
//             Doublets.push_back(Doublet);
//         }
//     }

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    HJets Neutrinos = Event->GetParticles()->GetNeutrinos();

    std::vector<HSextet> Sextets;
    for(const auto& Doublet1 : Doublets)
    for(const auto& Doublet2 : Doublets){
        if(Doublet1.GetJet1() == Doublet2.GetJet1()) continue;
        if(Doublet1.GetJet2() == Doublet2.GetJet2()) continue;
        HQuartet Quartet(Doublet1,Doublet2,MissingEt);
        Quartet.SetTag(GetQuartetTag(Quartet));
        if(Quartet.GetTag()!=State) continue;
        std::vector<HSextet> PreSextets;
        if (State == HSignal) {
            HSextet Sextet = Quartet.GetSextet(Neutrinos);
            PreSextets.push_back(Sextet);
        } else{
             PreSextets = Quartet.GetSextets();
            }
            for(auto & Sextet : PreSextets){
            if(Sextet.GetSextetJet().m()<0) continue;
            if(Sextet.GetError()<0) continue; // FIXME Was mach das noch mal?
            Sextet.SetTag(Quartet.GetTag());
            Sextets.push_back(Sextet);
        }
    }

//     HJets HeavyHiggsLeptons;
//     HJets OtherLeptons;
//     for (auto & Lepton : Leptons) {
//         if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Lepton.user_index()))) != end(JetTag->HeavyParticles)) HeavyHiggsLeptons.push_back(Lepton);
//         else OtherLeptons.push_back(Lepton);
//     }
//     if (State == HSignal && HeavyHiggsLeptons.size() < 2) {
//         Print(HInformation, "Not enough Higgs leptons", HeavyHiggsLeptons.size());
//         return HeavyHiggsBranches;
//     }
//     Print(HDebug, "Leptons", Leptons.size(), HeavyHiggsLeptons.size(), OtherLeptons.size());
//
//     std::vector<HDoublet> JetLeptonPairs;
//     if (State == HSignal) {
//         Print(HInformation, "Higgs Jets", HeavyHiggsJets.size());
//         for (const auto & Jet : HeavyHiggsJets) {
//             for (const auto & Lepton : HeavyHiggsLeptons) {
//                 Print(HDebug, "HeavyHiggs User Indices", Jet.user_index(), Lepton.user_index());
//                 if (Lepton.user_index() != Jet.user_index()) continue;
//                 HDoublet JetPair(Jet, Lepton);
//                 JetPair.SetTag(1);
//                 JetLeptonPairs.push_back(JetPair);
//             }
//         }
//     } else if (State == HBackground) {
//         for (const auto & Jet : HeavyHiggsJets) {
//             for (const auto & Lepton : HeavyHiggsLeptons) {
//                 if (Lepton.user_index() == Jet.user_index()) continue;
//                 HDoublet JetPair(Jet, Lepton);
//                 JetPair.SetTag(0);
//                 JetLeptonPairs.push_back(JetPair);
//             }
//         }
//         for (const auto & Jet : OtherJets) {
//             for (const auto & Lepton : HeavyHiggsLeptons) {
//                 HDoublet JetPair(Jet, Lepton);
//                 JetPair.SetTag(0);
//                 JetLeptonPairs.push_back(JetPair);
//             }
//         }
//         for (const auto & Jet : HeavyHiggsJets) {
//             for (const auto & Lepton : OtherLeptons) {
//                 HDoublet JetPair(Jet, Lepton);
//                 JetPair.SetTag(0);
//                 JetLeptonPairs.push_back(JetPair);
//             }
//         }
//         for (const auto & Jet : OtherJets) {
//             for (const auto & Lepton : OtherLeptons) {
//                 HDoublet JetPair(Jet, Lepton);
//                 JetPair.SetTag(0);
//                 JetLeptonPairs.push_back(JetPair);
//             }
//         }
//     }
//     Print(HDebug, "Pairs", JetLeptonPairs.size());
//     if (JetLeptonPairs.size() < 2) {
//         return HeavyHiggsBranches;
//     }
//
//     for (auto & JetPair : JetLeptonPairs) {
//         TopLeptonicTagger->FillBranch(JetPair);
//         JetPair.SetBdt(TopLeptonicReader->GetBdt());
//         Print(HDebug, "Top Bdt", JetPair.GetBdt());
//     }


//     std::vector<HSextet> TriplePairs;
//
//     for (std::vector<HDoublet>::iterator Pair1 = JetLeptonPairs.begin(); Pair1 != JetLeptonPairs.end(); ++Pair1) {
//         for (std::vector<HDoublet>::iterator Pair2 = std::next(Pair1); Pair2 != JetLeptonPairs.end(); ++Pair2) {
//             Print(HInformation, "NextPair");
//             if ((*Pair1).GetJet1() == (*Pair2).GetJet1()) {
//                 continue;
//             }
//             if ((*Pair1).GetJet2() == (*Pair2).GetJet2()) {
//                 continue;
//             }
//             HQuartet PairPair((*Pair1), (*Pair2), MissingEt);
//             HSextet TriplePair = PairPair.GetSextet(Neutrinos);
//             if (TriplePair.GetSextetJet().m() <= 0) {
//                 continue;
//             }
//             if (TriplePair.GetError() > 0) {
//                 TriplePairs.push_back(TriplePair);
//             }
//         }
//     }

//     Print(HInformation, "Number of Heavy Higgses", TriplePairs.size());
//     if (TriplePairs.size() < 1) {
//         return HeavyHiggsBranches;
//     }

    if (State == HSignal && Sextets.size() > 1) {
        Print(HError, "Higgs Candidates", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end(), SortByError());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    for (const auto & Sextet : Sextets) {
        HHeavyHiggsLeptonicBranch* HeavyHiggsLeptonicBranch = new HHeavyHiggsLeptonicBranch();
        FillBranch(HeavyHiggsLeptonicBranch, Sextet);
        HeavyHiggsBranches.push_back(HeavyHiggsLeptonicBranch);
    }


    return HeavyHiggsBranches;

}

hanalysis::HObject::HState hanalysis::HHeavyHiggsLeptonicTagger::GetQuartetTag(const HQuartet &Quartet)
{
    Print(HInformation, "Get Triple Tag");

    if (std::abs(Quartet.GetDoublet1().GetJet1().user_index() != TopId)) return HBackground;
    if (Quartet.GetDoublet1().GetJet1().user_index() != -Quartet.GetDoublet2().GetJet1().user_index()) return HBackground;
    if (std::abs(Quartet.GetDoublet1().GetJet2().user_index() != WId)) return HBackground;
    if (Quartet.GetDoublet2().GetJet2().user_index() != -Quartet.GetDoublet2().GetJet2().user_index()) return HBackground;

    return HSignal;
}

void hanalysis::HHeavyHiggsLeptonicTagger::FillBranch(const hanalysis::HSextet& TriplePair)
{
    Print(HInformation, "FillPairTagger", TriplePair.GetBdt());

    FillBranch(Branch, TriplePair);

}

