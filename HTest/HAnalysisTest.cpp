# include "HAnalysisTest.hh"

htest::HAnalysis::HAnalysis()
{

    Print(HNotification, "Constructor");

}

HStrings htest::HAnalysis::GetStudyNameVector(){

    HStrings StudyNameVector = {"Test","Second"};

    return StudyNameVector;

}

std::vector<hanalysis::HFile*> htest::HAnalysis::GetFiles(const std::string &StudyName)
{

    Print(HNotification, "Set File Vector", StudyName);

    std::vector<hanalysis::HFile*> Files;

    hdelphes::HFile *Background = new hdelphes::HFile("pp-ttbb");
        Files.push_back(Background);

//     HFile *Even = new HFile("pp-x0tt-bblvlv","even");
//     FileVector.push_back(Even);

    Print(HNotification, "Files prepared");

    return Files;
}


void htest::HAnalysis::NewBranches(ExRootTreeWriter *TreeWriter)
{
    Print(HNotification, "New File");

    CandidateBranch = TreeWriter->NewBranch("Candidate", HCandidateBranch::Class());

}

void htest::HAnalysis::CloseFile()
{
    Print(HNotification, "Close File");

}

// class htest::HJetTag : public hanalysis::HJetTag {
// 
//     int GetBranchId(int, int);
// 
// };

// int htest::HJetTag::GetBranchId(const int ParticleId, int BranchId)
// {
// 
//     Print(HInformation, "Get Mother Id");
// 
//     if (RadiationParticles.find(std::abs(ParticleId)) != end(RadiationParticles) && HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)) {
//         BranchId = IsrId;
//     } else if (std::abs(ParticleId) == BottomId && (std::abs(BranchId) != TopId && std::abs(BranchId) != CpvHiggsId)) {
//         BranchId = ParticleId;
//     } else if (std::abs(ParticleId) == TopId || std::abs(ParticleId) == CpvHiggsId) {
//         BranchId = ParticleId;
//     }
// 
//     Print(HDetailed, "Mother Id", BranchId);
// 
// 
//     return BranchId;
// 
// }

bool htest::HAnalysis::Analysis(hanalysis::HEvent *Event, const std::string &StudyName)
{

    Print(HInformation, "Analysis", StudyName);

    hanalysis::HJetTag * const HeavyHiggsJetTag = new hanalysis::HJetTag;
//     Event->GetTaggedJets(HeavyHiggsJetTag);


    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

    Candidate->Pt = float(Event->GetJets()->GetTaggedJets(HeavyHiggsJetTag).front().pt());

    if (Candidate->Pt > 100 ) {

    return 0;

    } else {

      return 1;

    }

}

