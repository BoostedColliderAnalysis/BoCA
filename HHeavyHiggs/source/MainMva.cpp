#include "HAnalysisHeavyHiggsMva.hh"


void RunTagger(const std::string TaggerName, const hheavyhiggs::HAnalysisMva::HTagger Tagger)
{

    std::cout << "Run Tagger " << TaggerName << std::endl;;

    hanalysis::HFactory *Factory;
    bool HasFactory = 0;
    hheavyhiggs::HAnalysisMva *Analysis = new hheavyhiggs::HAnalysisMva();

    TFile *File(0);
    std::string FileName = Analysis->GetProjectName() + "/" + TaggerName + ".root";
    if (!gSystem->AccessPathName(FileName.c_str()))File = TFile::Open(FileName.c_str());
    else Analysis->AnalysisLoop(Tagger);

    FileName = Analysis->GetProjectName() + "/Mva" + TaggerName + ".root";
    if (!gSystem->AccessPathName(FileName.c_str()))File = TFile::Open(FileName.c_str());
    else {
        Analysis->GetFiles(TaggerName);
        if (Tagger == hheavyhiggs::HAnalysisMva::HBottomTagger) Factory = new hanalysis::HFactory(Analysis->BottomTagger);
        if (Tagger == hheavyhiggs::HAnalysisMva::HWTagger) Factory = new hanalysis::HFactory(Analysis->WTagger);
        if (Tagger == hanalysis::HAnalysis::HTopLeptonicTagger) Factory = new hanalysis::HFactory(Analysis->TopLeptonicTagger);
        if (Tagger == hanalysis::HAnalysis::HTopHadronicTagger) Factory = new hanalysis::HFactory(Analysis->TopHadronicTagger);
        if (Tagger == hanalysis::HAnalysis::HHeavyHiggsLeptonicTagger) Factory = new hanalysis::HFactory(Analysis->HeavyHiggsLeptonicTagger);
        if (Tagger == hanalysis::HAnalysis::HHeavyHiggsHadronicTagger) Factory = new hanalysis::HFactory(Analysis->HeavyHiggsHadronicTagger);
        if (Tagger == hanalysis::HAnalysis::HLeptonicEventTagger) Factory = new hanalysis::HFactory(Analysis->LeptonicEventTagger);
        if (Tagger == hanalysis::HAnalysis::HHadronicEventTagger) Factory = new hanalysis::HFactory(Analysis->HadronicEventTagger);
        HasFactory = 1;
    }

    if (HasFactory) delete Factory;
    delete Analysis;
}

int main()
{

    RunTagger("Bottom", hheavyhiggs::HAnalysisMva::HBottomTagger);
    RunTagger("W", hheavyhiggs::HAnalysisMva::HWTagger);
    RunTagger("TopLeptonic", hanalysis::HAnalysis::HTopLeptonicTagger);
    RunTagger("TopHadronic", hanalysis::HAnalysis::HTopHadronicTagger);
    RunTagger("HeavyHiggsLeptonic", hanalysis::HAnalysis::HHeavyHiggsLeptonicTagger);
    RunTagger("HeavyHiggsHadronic", hanalysis::HAnalysis::HHeavyHiggsHadronicTagger);
    RunTagger("LeptonicEvent",hanalysis::HAnalysis::HLeptonicEventTagger);
    RunTagger("HadronicEvent",hanalysis::HAnalysis::HHadronicEventTagger);

    return 1;

}
