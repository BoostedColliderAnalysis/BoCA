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



bool HAnalysisTest::Analysis()
{

    Print(2, "Analysis", StudyName);

    Event->Jets->GetTaggedJets();


    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

    Candidate->Pt = float(Event->Jets->JetVector.front().pt());

    if (Candidate->Pt > 100 ) {

    return 0;

    } else {

      return 1;

    }

}

