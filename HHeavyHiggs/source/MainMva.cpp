#include "HAnalysisHeavyHiggsMva.hh"
#include "HMvaEvent.hh"


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
        if (Tagger == hanalysis::HAnalysis::HTopTagger) {
            Factory = new hanalysis::HFactory(Analysis->LeptonicTopTagger);
        }
        if (Tagger == hanalysis::HAnalysis::HHiggsTagger) {
            Factory = new hanalysis::HFactory(Analysis->HeavyHiggsTagger);
        }
        if (Tagger == hanalysis::HAnalysis::HEventTagger) {
            Factory = new hanalysis::HFactory(Analysis->HeavyHiggsEventTagger);
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
    RunTagger("HeavyHiggs", hanalysis::HAnalysis::HHiggsTagger);
    RunTagger("Signal",hanalysis::HAnalysis::HEventTagger);

    return 1;

}
