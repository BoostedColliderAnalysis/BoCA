# include "HMvaHiggsCpv.hh"

hbtagger::HMva::HMva()
{

    Print(HNotification , "Constructor");

    AnalysisName = "HiggsCpv";

    SignalNames = {"JetPair"};

    BackgroundNames = {"JetPair"};

    TestName = "JetPair";

    SignalTreeNames = {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};

    BackgroundTreeNames = {"pp-bbtt-bblvlv-background"};

    TestTreeNames = {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"};

    CandidateBranchName = "Candidate";

    SpectatorBranchName = "Lepton";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    DoLatex = 1;

    Candidate = new HCandidateBranch();

    DefineVariables();

//     Cut = "abs(Candidate.Pull11)<3.2&&abs(Candidate.Pull12)<3.2&&abs(Candidate.Pull21)<3.2&&/*/*abs*/*/(Candidate.Pull22)<3.2&&abs(Candidate.Pull31)<3.2&&abs(Candidate.Pull32)<3.2&&abs(Candidate.Pull41)<3.2&&abs(Candidate.Pull42)<3.2";

}

hbtagger::HMva::~HMva()
{

    Print(HNotification , "Constructor");

    delete Candidate;

}

void hbtagger::HMva::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Candidate->InvMass1, "Candidate.InvMass1", "InvMass1", "GeV"));
    Observables.push_back(NewObservable(&Candidate->InvMass2, "Candidate.InvMass2", "InvMass2", "GeV"));
    Observables.push_back(NewObservable(&Candidate->InvMass3, "Candidate.InvMass3", "InvMass3", "GeV"));
    Observables.push_back(NewObservable(&Candidate->ScalarHt, "Candidate.ScalarHt", "ScalarHt", "GeV"));
    Observables.push_back(NewObservable(&Candidate->DeltaR1, "Candidate.DeltaR1", "DeltaR1"));
    Observables.push_back(NewObservable(&Candidate->DeltaR2, "Candidate.DeltaR2", "DeltaR2"));
    Observables.push_back(NewObservable(&Candidate->DeltaR3, "Candidate.DeltaR3", "DeltaR3"));
    Observables.push_back(NewObservable(&Candidate->JetNumber, "Candidate.JetNumber", "JetNumber"));
    Observables.push_back(NewObservable(&Candidate->BottomNumber, "Candidate.BottomNumber", "BottomNumber"));
//     Observables.push_back(NewObservable(&Candidate->Pull11, "Candidate.Pull11", "Pull11"));
//     Observables.push_back(NewObservable(&Candidate->Pull12, "Candidate.Pull12", "Pull12"));
//     Observables.push_back(NewObservable(&Candidate->Pull21, "Candidate.Pull21", "Pull21"));
//     Observables.push_back(NewObservable(&Candidate->Pull22, "Candidate.Pull22", "Pull22"));
//     Observables.push_back(NewObservable(&Candidate->Pull31, "Candidate.Pull31", "Pull31"));
//     Observables.push_back(NewObservable(&Candidate->Pull32, "Candidate.Pull32", "Pull32"));
    Observables.push_back(NewObservable(&Candidate->Vertex11, "Candidate.Vertex11", "Vertex11"));
    Observables.push_back(NewObservable(&Candidate->Vertex12, "Candidate.Vertex12", "Vertex12"));
    Observables.push_back(NewObservable(&Candidate->Vertex21, "Candidate.Vertex21", "Vertex21"));
    Observables.push_back(NewObservable(&Candidate->Vertex22, "Candidate.Vertex22", "Vertex22"));
    Observables.push_back(NewObservable(&Candidate->Vertex31, "Candidate.Vertex31", "Vertex31"));
    Observables.push_back(NewObservable(&Candidate->Vertex32, "Candidate.Vertex32", "Vertex32"));

    Spectators.push_back(NewObservable(&Candidate->HiggsTag, "Candidate.HiggsTag", "Higgs Tag"));
    Spectators.push_back(NewObservable(&Candidate->TopTag, "Candidate.TopTag", "Top Tag"));

    Print(HNotification, "Variables defined");

}


void hbtagger::HMva::ApplyBdt(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
{
    Print(HNotification, "Apply Bdt");

    const TClonesArray *const CandidateClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(CandidateBranchName.c_str());
//   const TClonesArray *const SpectatorClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(SpectatorBranchName.c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *CandidateBranch = TreeWriter->NewBranch(CandidateBranchName.c_str(), HCandidateBranch::Class());
//   ExRootTreeBranch *LeptonBranch = TreeWriter->NewBranch(SpectatorBranchName.c_str(), HLeptonBranch::Class());

    const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();

    for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        for (int CandidateNumber = 0; CandidateNumber < CandidateClonesArray->GetEntriesFast(); ++CandidateNumber) {

            (*Candidate) = *((HCandidateBranch *) CandidateClonesArray->At(CandidateNumber));

            HCandidateBranch *ExportCandidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

            (*ExportCandidate) = *Candidate;

            const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);

            float SigEff;
            const int StepSize = 50;
            for (SigEff = 0; SigEff < StepSize; ++SigEff) {

                bool CutEvaluation = Reader->EvaluateMVA(CutMethodName, SigEff / StepSize);

                if (CutEvaluation) break;

            }

            ExportCandidate->JetBdtTag = BdtEvaluation;
            ExportCandidate->JetCutSigEff = SigEff / StepSize;

            ExportCandidate->TopBdtTag = BdtEvaluation;
            ExportCandidate->TopCutSigEff = SigEff / StepSize;

        }

//     for (int CandidateNumber = 0; CandidateNumber < SpectatorClonesArray->GetEntriesFast(); ++CandidateNumber) {

//       HLeptonBranch *Lepton = (HLeptonBranch *) SpectatorClonesArray->At(CandidateNumber);

//       HLeptonBranch *ExportLepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());
//       (*ExportLepton) = *Lepton;

//     }

        TreeWriter->Fill();
        TreeWriter->Clear();

    }

    TreeWriter->Write();
    delete TreeWriter;

}


HReaderStruct hbtagger::HMva::CutLoop(const ExRootTreeReader *const TreeReader, HReaderStruct &ReaderStruct)
{

    Print(HNotification, "Cut Loop");

    int ObservableSum = Observables.size();

    Print(HNotification, "Observables", Observables.size());

    ReaderStruct.HiggsSum = 0;
    ReaderStruct.TopSum = 0;
    ReaderStruct.FatJetSum = 0;

    ReaderStruct.TopEventSum = 0;
    ReaderStruct.HiggsEventSum = 0;

    ReaderStruct.EventVector.assign(ObservableSum, 0);
    ReaderStruct.TopEventVector.assign(ObservableSum, 0);
    ReaderStruct.HiggsEventVector.assign(ObservableSum, 0);
    ReaderStruct.CutFlowVector.assign(ObservableSum, 0);
    ReaderStruct.FatJetVector.assign(ObservableSum, 0);
    ReaderStruct.HiggsVector.assign(ObservableSum, 0);
    ReaderStruct.TopVector.assign(ObservableSum, 0);

    Print(HInformation, "Vectors assigned");

    const TClonesArray *const ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(CandidateBranchName.c_str());


    const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();
    for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {
        Print(HDebug, "Event Loop");

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        std::vector<bool> CandidateEventCut(ObservableSum, 1);
        std::vector<bool> TopEventCut(ObservableSum, 1);
        std::vector<bool> HiggsEventCut(ObservableSum, 1);
        bool HasHiggs = 0;;
        bool HasTop = 0;

        for (int CandidateNumber = 0; CandidateNumber < ClonesArray->GetEntriesFast(); ++CandidateNumber) {

            Print(HDebug, "Candidate Loop");
            ++ReaderStruct.FatJetSum;

            if (Candidate->TopTag) {

                ++ReaderStruct.TopSum;
                HasTop = 1;

            }

            if (Candidate->HiggsTag) {

                ++ReaderStruct.HiggsSum;
                HasHiggs = 1;

            }

            (*Candidate) = *((HCandidateBranch *) ClonesArray->At(CandidateNumber));

            bool ParticleCut = 0;
            for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

                Print(HDebug, "Observable Loop");

                Print(HDebug, "Error", ReaderStruct.CutsMin[ObservableNumber]);

                if (*Observables[ObservableNumber].Value < ReaderStruct.CutsMin[ObservableNumber]
                        || *Observables[ObservableNumber].Value > ReaderStruct.CutsMax[ObservableNumber]) {

                    Print(HDebug, "we are here", 1);

                    ParticleCut = 1;

                } else {

                    Print(HDebug, "we are here", 2);
                    ++ReaderStruct.CutFlowVector[ObservableNumber];

                }
                Print(HDebug, "Struct filled");

                if (!ParticleCut) {

                    ++ReaderStruct.FatJetVector[ObservableNumber];
                    CandidateEventCut[ObservableNumber] = 0;

                    if (Candidate->TopTag) {

                        ++ReaderStruct.TopVector[ObservableNumber];
                        TopEventCut[ObservableNumber] = 0;

                    }

                    if (Candidate->HiggsTag) {

                        ++ReaderStruct.HiggsVector[ObservableNumber];
                        HiggsEventCut[ObservableNumber] = 0;

                    }

                }

            }

        }

        if (HasHiggs) ++ReaderStruct.HiggsEventSum;
        if (HasTop) ++ReaderStruct.TopEventSum;

        for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

            if (!CandidateEventCut[ObservableNumber]) {

                ++ReaderStruct.EventVector[ObservableNumber];
                if (!HiggsEventCut[ObservableNumber]) ++ReaderStruct.HiggsEventVector[ObservableNumber];
                if (!TopEventCut[ObservableNumber]) ++ReaderStruct.TopEventVector[ObservableNumber];

            }

        }

    }

    return ReaderStruct;

}
