# include "HAnalysisTest.hh"

HAnalysisTest::HAnalysisTest()
{

    Print(1, "Constructor");

    ProjectName = "Test";

}

vector<string> HAnalysisTest::GetStudyNameVector(){

    vector<string> StudyNameVector = {"Test","Second"};

    return StudyNameVector;

}

void HAnalysisTest::SetFileVector()
{

    Print(1, "Set File Vector", StudyName);

    HFileDelphes *Background = new HFileDelphes("pp-ttbb");
        FileVector.push_back(Background);

//     HFileDelphes *Even = new HFileDelphes("pp-x0tt-bblvlv","even");
//     FileVector.push_back(Even);

    int AnalysisSum = FileVector.size();
    Print(1, "Files prepared", AnalysisSum);

}


void HAnalysisTest::NewFile()
{
    Print(1, "New File");

    CandidateBranch = TreeWriter->NewBranch("Candidate", HCandidateBranch::Class());

}

void HAnalysisTest::CloseFile()
{
    Print(1, "Close File");

}

class HHeavyHiggsJetTag : public HJetTag {
    
    int GetBranchId(int, int);
    
};

int HHeavyHiggsJetTag::GetBranchId(const int ParticleId, int BranchId)
{
    
    Print(2, "Get Mother Id");
    
    if (InitialState.find(abs(ParticleId)) != end(InitialState) && MotherParticle.find(abs(BranchId)) == end(MotherParticle)) {
        BranchId = IsrId;
    } else if (abs(ParticleId) == BottomId && (abs(BranchId) != TopId && abs(BranchId) != CpvHiggsId)) {
        BranchId = ParticleId;
    } else if (abs(ParticleId) == TopId || abs(ParticleId) == CpvHiggsId) {
        BranchId = ParticleId;
    }
    
    Print(4, "Mother Id", BranchId);
    
    
    return BranchId;
    
}

bool HAnalysisTest::Analysis()
{

    Print(2, "Analysis", StudyName);
    
    const HHeavyHiggsJetTag * const HeavyHiggsJetTag = new HHeavyHiggsJetTag;
    Event->GetTaggedJets(HeavyHiggsJetTag);


    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

    Candidate->Pt = float(Event->Jets->Jets.front().pt());

    if (Candidate->Pt > 100 ) {

    return 0;

    } else {

      return 1;

    }

}

