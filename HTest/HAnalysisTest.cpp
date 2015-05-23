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

// class htest::JetTag : public analysis::JetTag {
//
//     int GetBranchId(int, int);
//
// };

// int htest::JetTag::GetBranchId(const int particle_id, int BranchId)
// {
//
//     Print(kInformation, "Get Mother Id");
//
//     if (RadiationParticles.find(std::abs(particle_id)) != end(RadiationParticles) && HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)) {
//         BranchId = IsrId;
//     } else if (std::abs(particle_id) == BottomId && (std::abs(BranchId) != TopId && std::abs(BranchId) != CpvHiggsId)) {
//         BranchId = particle_id;
//     } else if (std::abs(particle_id) == TopId || std::abs(particle_id) == CpvHiggsId) {
//         BranchId = particle_id;
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

    analysis::JetTag  HeavyHiggsjet_tag;
//     event.GetTaggedJets(HeavyHiggsjet_tag);


    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

    Candidate->Pt = float(event.hadrons().GetTaggedJets(HeavyHiggsjet_tag).front().pt());

    if (Candidate->Pt > 100 ) {

    return 0;

    } else {

      return 1;

    }

}

