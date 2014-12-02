#include "HAnalysisHeavyHiggsMva.hh"
#include "HMvaEvent.hh"
// #include "HMvaHiggs.hh"
// #include "HMvaBottom.hh"
// #include "HMvaTop.hh"

// int main()
// {
//
//     hmva::HMva *Mva;
//     hmva::HFactory *Factory;
// //     HReader * Reader;
//     hheavyhiggs::HAnalysisMva *Analysis = new hheavyhiggs::HAnalysisMva();
//
// //     Analysis->AnalysisLoop(hheavyhiggs::HAnalysisMva::HBottomTagger);
// // //     Mva = new hheavyhiggs::HMvaBottom();
//     Factory = new hmva::HFactory(Analysis->BottomTagger);
// //     Reader = new HReader (Analysis->BottomTagger);
// //     //     Analysis->SetMva(Mva);
// //     Analysis->BottomTagger->SetMva();
// //
//     Analysis->AnalysisLoop(hheavyhiggs::HAnalysisMva::HTopTagger);
// // //     Mva = new hheavyhiggs::HMvaTop();
//     Factory = new hmva::HFactory(Analysis->LeptonicTopTagger);
// //     Analysis->LeptonicTopTagger->SetMva();
// // //
// //     Analysis->AnalysisLoop(hheavyhiggs::HAnalysisMva::HHiggsTagger);
// // //     Mva = new hheavyhiggs::HMvaHiggs();
// //     Factory = new hmva::HFactory(Analysis->HeavyHiggsTagger);
// //     Analysis->HeavyHiggsTagger->SetMva();
// // //
// //     Analysis->AnalysisLoop(hanalysis::HAnalysis::HEventTagger);
// //     Mva = new hheavyhiggs::HMvaEvent();
// //     Factory = new hmva::HFactory(Mva);
// //     Analysis->SetMva(Mva);
//
//     delete Factory;
//     delete Mva;
//     delete Analysis;
//
//     return 1;
//
// }


void RunTagger(const std::string TaggerName, const hheavyhiggs::HAnalysisMva::HTagger Tagger)
{

    std::cout << "Run Tagger " << TaggerName << std::endl;;

    hanalysis::HFactory *Factory;
    bool HasFactory = 0;
    hheavyhiggs::HAnalysisMva *Analysis = new hheavyhiggs::HAnalysisMva();

    TFile *File(0);
    std::string FileName = Analysis->GetProjectName() + "/" + TaggerName + ".root";
    if (!gSystem->AccessPathName(FileName.c_str()))
        File = TFile::Open(FileName.c_str());
    else
        Analysis->AnalysisLoop(Tagger);

    FileName = Analysis->GetProjectName() + "/Mva" + TaggerName + ".root";
    if (!gSystem->AccessPathName(FileName.c_str()))
        File = TFile::Open(FileName.c_str());
    else {
        Analysis->GetFiles(TaggerName);
        if (Tagger == hheavyhiggs::HAnalysisMva::HBottomTagger) {
          Factory = new hanalysis::HFactory(Analysis->BottomTagger);
        }
        if (Tagger == hanalysis::HAnalysis::HTopTagger){
          Factory = new hanalysis::HFactory(Analysis->LeptonicTopTagger);
        }
        if (Tagger == hheavyhiggs::HAnalysisMva::HHiggsTagger){
          Factory = new hanalysis::HFactory(Analysis->HeavyHiggsTagger);
        }
        HasFactory = 1;
    }

    if (HasFactory) delete Factory;
    delete Analysis;
}

int main()
{

    RunTagger("Bottom", hheavyhiggs::HAnalysisMva::HBottomTagger);
    RunTagger("Top", hanalysis::HAnalysis::HTopTagger);
    RunTagger("Higgs", hanalysis::HAnalysis::HHiggsTagger);
    //     RunTagger("EventTagger",hanalysis::HAnalysis::HEventTagger);


    hanalysis::HFactory *Factory;
    hheavyhiggs::HAnalysisMva *Analysis = new hheavyhiggs::HAnalysisMva();

    //     TFile *File(0);
    //     std::string FileName = "./Bottom.root";
    //     if (!gSystem->AccessPathName(FileName))
    //         File = TFile::Open(FileName);
    //     else
    //         Analysis->AnalysisLoop(hheavyhiggs::HAnalysisMva::HBottomTagger);
    //
    //     FileName = "./MvaBottom.root";
    //     if (!gSystem->AccessPathName(FileName))
    //         File = TFile::Open(FileName);
    //     else
    //         Factory = new hmva::HFactory(Analysis->BottomTagger);
    //
    //
    //     FileName = "./Top.root";
    //     if (!gSystem->AccessPathName(FileName))
    //         File = TFile::Open(FileName);
    //     else
    //         Analysis->AnalysisLoop(hheavyhiggs::HAnalysis::HTopTagger);
    //
    //     FileName = "./MvaTop.root";
    //     if (!gSystem->AccessPathName(FileName))
    //         File = TFile::Open(FileName);
    //     else
    //         Factory = new hmva::HFactory(Analysis->LeptonicTopTagger);
    //
    //
    //     FileName = "./Higgs.root";
    //     if (!gSystem->AccessPathName(FileName))
    //         File = TFile::Open(FileName);
    //     else
    //         Analysis->AnalysisLoop(hheavyhiggs::HAnalysis::HHiggsTagger);
    //
    //     FileName = "./MvaHiggs.root";
    //     if (!gSystem->AccessPathName(FileName))
    //         File = TFile::Open(FileName);
    //     else
    //         Factory = new hmva::HFactory(Analysis->HiggsTagger);

    Analysis->AnalysisLoop(hanalysis::HAnalysis::HEventTagger);
    hanalysis::HMva *Mva = new hheavyhiggs::HMvaEvent();
    Factory = new hanalysis::HFactory(Mva);

    delete Factory;
    delete Mva;
    delete Analysis;

    return 1;

}
