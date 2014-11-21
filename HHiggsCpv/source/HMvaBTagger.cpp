# include "HMvaBTagger.hh"

hhiggscpv::HMvaBTagger::HMvaBTagger()
{

    Print(HNotification , "Constructor");

    AnalysisName = "HiggsCpv";

    TaggerName = "BTagger";

    SignalNames = {"Bottom"};

    BackgroundNames = {"LightJet"};

    TestName = "Test";

    TestTreeNames = {"pp-bbtt-bblvlv-background","pp-x0tt-bblvlv-even"};

    SignalTreeNames = TestTreeNames;

    BackgroundTreeNames = TestTreeNames;

    CandidateBranchName = "BTagger";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    DoLatex = 1;

    Candidate = new HBTaggerBranch();

    DefineVariables();

//     Cut = "abs(Candidate.Pull11)<3.2&&abs(Candidate.Pull12)<3.2&&abs(Candidate.Pull21)<3.2&&/*/*abs*/*/(Candidate.Pull22)<3.2&&abs(Candidate.Pull31)<3.2&&abs(Candidate.Pull32)<3.2&&abs(Candidate.Pull41)<3.2&&abs(Candidate.Pull42)<3.2";

//     DebugLevel = HDebug;

}

hhiggscpv::HMvaBTagger::~HMvaBTagger()
{

    Print(HNotification , "Constructor");

    delete Candidate;

}

void hhiggscpv::HMvaBTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Candidate->VertexMass, "BTagger.VertexMass", "VertexMass", "GeV"));
//     Observables.push_back(NewObservable(&Candidate->JetMass, "BTagger.JetMass", "JetMass", "GeV"));
    Observables.push_back(NewObservable(&Candidate->VertexNumber, "BTagger.VertexNumber", "VertexNumber"));
    Observables.push_back(NewObservable(&Candidate->Vertex, "BTagger.Vertex", "Vertex"));

//     Spectators.push_back(NewObservable(&Candidate->BTag, "BTagger.BTag", "BTag"));

    Print(HNotification, "Variables defined");

}

// float hhiggscpv::HMvaBTagger::GetBdt(HBTaggerBranch *Branch, TMVA::Reader *Reader){
float hhiggscpv::HMvaBTagger::GetBdt(TObject *Branch, TMVA::Reader *Reader){

  Print(HInformation, "Get Bdt",BdtMethodName);

//     *Candidate = *Branch;

  HBTaggerBranch *TempBranch = static_cast<HBTaggerBranch*>(Branch);
    *Candidate = *TempBranch;

    Print(HInformation, "Mass", Candidate->VertexMass);

//     Reader->

    const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);

    Print(HInformation,"BTagger Bdt",BdtEvaluation);

    return ((BdtEvaluation+1)/2);

}


void hhiggscpv::HMvaBTagger::ApplyBdt(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
{
    Print(HNotification, "Apply Bdt");

    const TClonesArray *const CandidateClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(CandidateBranchName.c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *CandidateBranch = TreeWriter->NewBranch(CandidateBranchName.c_str(), HBTaggerBranch::Class());

    const int EventSum = const_cast<ExRootTreeReader *>(TreeReader)->GetEntries();

    for (int EventNumber = 0; EventNumber < EventSum; ++EventNumber) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        for (int CandidateNumber = 0; CandidateNumber < CandidateClonesArray->GetEntriesFast(); ++CandidateNumber) {

            (*Candidate) = *((HBTaggerBranch *) CandidateClonesArray->At(CandidateNumber));

            HBTaggerBranch *ExportCandidate = static_cast<HBTaggerBranch *>(CandidateBranch->NewEntry());

            (*ExportCandidate) = *Candidate;

            const float BdtEvaluation = Reader->EvaluateMVA(BdtMethodName);

            float SigEff;
            const int StepSize = 50;
            for (SigEff = 0; SigEff < StepSize; ++SigEff) {

                bool CutEvaluation = Reader->EvaluateMVA(CutMethodName, SigEff / StepSize);

                if (CutEvaluation) break;

            }

//             ExportCandidate->BdtBTag = BdtEvaluation;
//             ExportCandidate->BCutSigEff = SigEff / StepSize;

        }


        TreeWriter->Fill();
        TreeWriter->Clear();

    }

    TreeWriter->Write();
    delete TreeWriter;

}


HReaderStruct hhiggscpv::HMvaBTagger::CutLoop(const ExRootTreeReader *const TreeReader, HReaderStruct &ReaderStruct)
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

//             if (Candidate->BTag) {

                ++ReaderStruct.TopSum;
                HasTop = 1;

//             }

            (*Candidate) = *((HBTaggerBranch *) ClonesArray->At(CandidateNumber));

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

//                     if (Candidate->BTag) {

                        ++ReaderStruct.TopVector[ObservableNumber];
                        TopEventCut[ObservableNumber] = 0;

//                     }

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
