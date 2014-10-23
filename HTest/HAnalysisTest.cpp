# include "HAnalysisTest.hh"

HAnalysisTest::HAnalysisTest()
{

    Print(1, "Constructor");

}

vector<string> HAnalysisTest::GetStudyNameVector(){

    vector<string> StudyNameVector = {"Test","Second"};

    return StudyNameVector;

}

vector<HFile*> HAnalysisTest::GetFiles(const string StudyName) const
{

    Print(1, "Set File Vector", StudyName);

    vector<HFile*> Files;

    HFileDelphes *Background = new HFileDelphes("pp-ttbb");
        Files.push_back(Background);

//     HFileDelphes *Even = new HFileDelphes("pp-x0tt-bblvlv","even");
//     FileVector.push_back(Even);

    Print(1, "Files prepared");

    return Files;
}


void HAnalysisTest::NewBranches(ExRootTreeWriter *TreeWriter)
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

    if (RadiationParticles.find(abs(ParticleId)) != end(RadiationParticles) && HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)) {
        BranchId = IsrId;
    } else if (abs(ParticleId) == BottomId && (abs(BranchId) != TopId && abs(BranchId) != CpvHiggsId)) {
        BranchId = ParticleId;
    } else if (abs(ParticleId) == TopId || abs(ParticleId) == CpvHiggsId) {
        BranchId = ParticleId;
    }

    Print(4, "Mother Id", BranchId);


    return BranchId;

}

bool HAnalysisTest::Analysis(HEvent* Event,string StudyName)
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

