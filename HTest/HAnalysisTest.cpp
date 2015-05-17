# include "HAnalysisTest.hh"

// htest::HAnalysis::HAnalysis()
// {
//
//     Print(kNotification, "Constructor");
//
// }

Strings htest::HAnalysis::GetStudyNameVector(){

    Strings StudyNameVector = {"Test","Second"};

    return StudyNameVector;

}

std::vector<analysis::File*> htest::HAnalysis::GetFiles(const std::string &StudyName)
{

    Print(kNotification, "Set File Vector", StudyName);

    std::vector<analysis::File*> Files;

    analysis::File *Background = new analysis::File("pp-ttbb");
        Files.emplace_back(Background);

//     HFile *Even = new HFile("pp-x0tt-bblvlv","even");
//     FileVector.emplace_back(Even);

    Print(kNotification, "Files prepared");

    return Files;
}


void htest::HAnalysis::NewBranches(ExRootTreeWriter *TreeWriter)
{
    Print(kNotification, "New File");

    CandidateBranch = TreeWriter->NewBranch("Candidate", HCandidateBranch::Class());

}

void htest::HAnalysis::CloseFile()
{
    Print(kNotification, "Close File");

}

// class htest::HJetTag : public analysis::HJetTag {
//
//     int GetBranchId(int, int);
//
// };

// int htest::HJetTag::GetBranchId(const int ParticleId, int BranchId)
// {
//
//     Print(kInformation, "Get Mother Id");
//
//     if (RadiationParticles.find(std::abs(ParticleId)) != end(RadiationParticles) && HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)) {
//         BranchId = IsrId;
//     } else if (std::abs(ParticleId) == BottomId && (std::abs(BranchId) != TopId && std::abs(BranchId) != CpvHiggsId)) {
//         BranchId = ParticleId;
//     } else if (std::abs(ParticleId) == TopId || std::abs(ParticleId) == CpvHiggsId) {
//         BranchId = ParticleId;
//     }
//
//     Print(kDetailed, "Mother Id", BranchId);
//
//
//     return BranchId;
//
// }

int htest::HAnalysis::Analysis(analysis::Event &event, const std::string &StudyName)
{

    Print(kInformation, "Analysis", StudyName);

    analysis::HJetTag  HeavyHiggsJetTag;
//     event.GetTaggedJets(HeavyHiggsJetTag);


    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

    Candidate->Pt = float(event.hadrons().GetTaggedJets(HeavyHiggsJetTag).front().pt());

    if (Candidate->Pt > 100 ) {

    return 0;

    } else {

      return 1;

    }

}

