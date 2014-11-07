# include "HAnalysisTest.hh"

htest::HAnalysis::HAnalysis()
{

    Print(1, "Constructor");

}

vector<string> htest::HAnalysis::GetStudyNameVector(){

    vector<string> StudyNameVector = {"Test","Second"};

    return StudyNameVector;

}

vector<hanalysis::HFile*> htest::HAnalysis::GetFiles(const string &StudyName) const
{

    Print(1, "Set File Vector", StudyName);

    vector<hanalysis::HFile*> Files;

    hanalysis::hdelphes::HFile *Background = new hanalysis::hdelphes::HFile("pp-ttbb");
        Files.push_back(Background);

//     HFile *Even = new HFile("pp-x0tt-bblvlv","even");
//     FileVector.push_back(Even);

    Print(1, "Files prepared");

    return Files;
}


void htest::HAnalysis::NewBranches(ExRootTreeWriter *TreeWriter)
{
    Print(1, "New File");

    CandidateBranch = TreeWriter->NewBranch("Candidate", HCandidateBranch::Class());

}

void htest::HAnalysis::CloseFile()
{
    Print(1, "Close File");

}

class htest::HJetTag : public hanalysis::HJetTag {

    int GetBranchId(int, int);

};

int htest::HJetTag::GetBranchId(const int ParticleId, int BranchId)
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

bool htest::HAnalysis::Analysis(hanalysis::HEvent *Event, const string &StudyName)
{

    Print(2, "Analysis", StudyName);

    HJetTag * const HeavyHiggsJetTag = new HJetTag;
//     Event->GetTaggedJets(HeavyHiggsJetTag);


    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

    Candidate->Pt = float(Event->GetJets()->GetTaggedJets(HeavyHiggsJetTag).front().pt());

    if (Candidate->Pt > 100 ) {

    return 0;

    } else {

      return 1;

    }

}

