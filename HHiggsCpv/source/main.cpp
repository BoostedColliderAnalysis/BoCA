# include "HAnalysisHiggsCpv.hh"
# include "HMvaEvent.hh"
# include "HMvaHiggs.hh"
# include "HMvaBottom.hh"
# include "HMvaTop.hh"
# include "Tagger.hh"

void RunTagger(const std::string TaggerName)
{

    std::cout << "Run Tagger " << TaggerName << std::endl;;

//     bool HasFactory = 0;
//     hhiggscpv::HAnalysis *Analysis = new hhiggscpv::HAnalysis();

//     TFile *File;
    std::string FileName = "HiggsCpv/" + TaggerName + ".root";
    if (gSystem->AccessPathName(FileName.c_str()))
//         File = TFile::Open(FileName.c_str());
//     else
//         Analysis->AnalysisLoop(analysis::Tagger::kReader);

    FileName = "HiggsCpv/Mva" + TaggerName + ".root";
    if (gSystem->AccessPathName(FileName.c_str()))
//         File = TFile::Open(FileName.c_str());
//     else
    {
//             Analysis->GetFiles(TaggerName);
//         if (Tagger == hhiggscpv::HAnalysis::HBottomTagger) {
//           analysis::Factory Factory =
//           analysis::Factory(Analysis->BottomTagger);
//         }
//         if (Tagger == analysis::HAnalysis::TopLeptonicTagger){
//           analysis::Factory Factory =
//           analysis::Factory(Analysis->LeptonicTopTagger);
//         }
//         if (Tagger == hhiggscpv::HAnalysis::HHiggsLeptonicTagger){
//           analysis::Factory Factory =
//           analysis::Factory(Analysis->HiggsTagger);
//         }
    }
//     delete Analysis;
}

int main()
{

    RunTagger("Bottom" );
    RunTagger("Top" );
    RunTagger("Higgs");
//     RunTagger("eventTagger",analysis::HAnalysis::EventTagger);


//    hhiggscpv::HAnalysis Analysis;

//     TFile *File(0);
//     std::string FileName = "./Bottom.root";
//     if (!gSystem->AccessPathName(FileName))
//         File = TFile::Open(FileName);
//     else
//         Analysis->AnalysisLoop(hhiggscpv::HAnalysis::HBottomTagger);
//
//     FileName = "./MvaBottom.root";
//     if (!gSystem->AccessPathName(FileName))
//         File = TFile::Open(FileName);
//     else
//         Factory = new hmva::Factory(Analysis->BottomTagger);
//
//
//     FileName = "./Top.root";
//     if (!gSystem->AccessPathName(FileName))
//         File = TFile::Open(FileName);
//     else
//         Analysis->AnalysisLoop(hhiggscpv::HAnalysis::TopLeptonicTagger);
//
//     FileName = "./MvaTop.root";
//     if (!gSystem->AccessPathName(FileName))
//         File = TFile::Open(FileName);
//     else
//         Factory = new hmva::Factory(Analysis->LeptonicTopTagger);
//
//
//     FileName = "./Higgs.root";
//     if (!gSystem->AccessPathName(FileName))
//         File = TFile::Open(FileName);
//     else
//         Analysis->AnalysisLoop(hhiggscpv::HAnalysis::HHiggsTagger);
//
//     FileName = "./MvaHiggs.root";
//     if (!gSystem->AccessPathName(FileName))
//         File = TFile::Open(FileName);
//     else
//         Factory = new hmva::Factory(Analysis->HiggsTagger);

//     Analysis.AnalysisLoop(analysis::Tagger::kReader);
    hhiggscpv::HMvaevent Mva;
    analysis::Factory Factory(Mva);

    return 1;

}
