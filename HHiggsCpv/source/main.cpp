#include "HAnalysisHiggsCpv.hh"
#include "HMvaEvent.hh"
#include "HMvaHiggs.hh"
#include "HMvaBottom.hh"
#include "HMvaTop.hh"
#include "HMva.hh"

void RunTagger(const std::string TaggerName, const hhiggscpv::HAnalysis::HTagger Tagger)
{

    std::cout << "Run Tagger " << TaggerName << std::endl;;

    hanalysis::HFactory *Factory;
    bool HasFactory = 0;
    hhiggscpv::HAnalysis *Analysis = new hhiggscpv::HAnalysis();

    TFile *File(0);
    std::string FileName = "HiggsCpv/" + TaggerName + ".root";
    if (!gSystem->AccessPathName(FileName.c_str()))
        File = TFile::Open(FileName.c_str());
    else
        Analysis->AnalysisLoop(Tagger);

    FileName = "HiggsCpv/Mva" + TaggerName + ".root";
    if (!gSystem->AccessPathName(FileName.c_str()))
        File = TFile::Open(FileName.c_str());
    else {
            Analysis->GetFiles(TaggerName);
        if (Tagger == hhiggscpv::HAnalysis::HBottomTagger) {
          Factory = new hanalysis::HFactory(Analysis->BottomTagger);
        }
        if (Tagger == hanalysis::HAnalysis::HTopTagger){
          Factory = new hanalysis::HFactory(Analysis->LeptonicTopTagger);
        }
        if (Tagger == hhiggscpv::HAnalysis::HHiggsTagger){
          Factory = new hanalysis::HFactory(Analysis->HiggsTagger);
        }
        HasFactory = 1;
    }

    if (HasFactory) delete Factory;
    delete Analysis;
}

int main()
{

    RunTagger("Bottom", hhiggscpv::HAnalysis::HBottomTagger);
    RunTagger("Top", hanalysis::HAnalysis::HTopTagger);
    RunTagger("Higgs", hanalysis::HAnalysis::HHiggsTagger);
//     RunTagger("EventTagger",hanalysis::HAnalysis::HEventTagger);


    hanalysis::HFactory *Factory;
    hhiggscpv::HAnalysis *Analysis = new hhiggscpv::HAnalysis();

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
//         Factory = new hmva::HFactory(Analysis->BottomTagger);
//
//
//     FileName = "./Top.root";
//     if (!gSystem->AccessPathName(FileName))
//         File = TFile::Open(FileName);
//     else
//         Analysis->AnalysisLoop(hhiggscpv::HAnalysis::HTopTagger);
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
//         Analysis->AnalysisLoop(hhiggscpv::HAnalysis::HHiggsTagger);
//
//     FileName = "./MvaHiggs.root";
//     if (!gSystem->AccessPathName(FileName))
//         File = TFile::Open(FileName);
//     else
//         Factory = new hmva::HFactory(Analysis->HiggsTagger);

    Analysis->AnalysisLoop(hanalysis::HAnalysis::HEventTagger);
    hanalysis::HMva *Mva = new hhiggscpv::HMvaEvent();
    Factory = new hanalysis::HFactory(Mva);

    delete Factory;
    delete Mva;
    delete Analysis;

    return 1;

}
