#include "HAnalysisHeavyHiggsMva.hh"


void RunTagger(const hanalysis::HAnalysis::HTagger Tagger)
{
    hanalysis::HFactory *Factory;
    bool HasFactory = 0;

    hheavyhiggs::HAnalysisMva *Analysis = new hheavyhiggs::HAnalysisMva();
    hanalysis::HObject::HState State = hanalysis::HObject::HSignal;
    std::string Name = Analysis->GetStudyNames(Tagger);

    Analysis->Print(Analysis->HError, "Tagger", Tagger, Name);

    TFile *File(0);
    std::string FileName = Analysis->GetProjectName() + "/" + Name + ".root";
    if (!gSystem->AccessPathName(FileName.c_str()))File = TFile::Open(FileName.c_str());

    else Analysis->AnalysisLoop(Tagger);

    FileName = Analysis->GetProjectName() + "/Mva" + Name + ".root";
    if (!gSystem->AccessPathName(FileName.c_str()))File = TFile::Open(FileName.c_str());
    else {
        Analysis->GetFiles(Tagger, hanalysis::HObject::HSignal);
        switch (Tagger) {
        case hanalysis::HAnalysis::HBottomTagger:
            Factory = new hanalysis::HFactory(Analysis->BottomTagger);
            break;
        case hanalysis::HAnalysis::HWTagger:
            Factory = new hanalysis::HFactory(Analysis->WTagger);
            break;
        case hanalysis::HAnalysis::HTopLeptonicTagger:
            Factory = new hanalysis::HFactory(Analysis->TopLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HTopHadronicTagger:
            Factory = new hanalysis::HFactory(Analysis->TopHadronicTagger);
            break;
        case hanalysis::HAnalysis::HTopSemiTagger:
            Factory = new hanalysis::HFactory(Analysis->TopSemiTagger);
            break;

        case hanalysis::HAnalysis::HHeavyHiggsLeptonicTagger:
            Factory = new hanalysis::HFactory(Analysis->HeavyHiggsLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsHadronicTagger:
            Factory = new hanalysis::HFactory(Analysis->HeavyHiggsHadronicTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsSemiTagger:
            Factory = new hanalysis::HFactory(Analysis->HeavyHiggsSemiTagger);
            break;

        case hanalysis::HAnalysis::HEventLeptonicTagger:
            Factory = new hanalysis::HFactory(Analysis->EventLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HEventHadronicTagger:
            Factory = new hanalysis::HFactory(Analysis->EventHadronicTagger);
            break;
        case hanalysis::HAnalysis::HEventSemiTagger:
            Factory = new hanalysis::HFactory(Analysis->EventSemiTagger);
            break;
        }
        HasFactory = 1;

    }

    if (HasFactory) delete Factory;
    delete Analysis;
}

int main()
{

    RunTagger(hanalysis::HAnalysis::HBottomTagger);
    RunTagger(hanalysis::HAnalysis::HWTagger);

    RunTagger(hanalysis::HAnalysis::HTopLeptonicTagger);
    RunTagger(hanalysis::HAnalysis::HTopHadronicTagger);
    RunTagger(hanalysis::HAnalysis::HTopSemiTagger);

    RunTagger(hanalysis::HAnalysis::HHeavyHiggsLeptonicTagger);
    RunTagger(hanalysis::HAnalysis::HHeavyHiggsSemiTagger);

    RunTagger(hanalysis::HAnalysis::HEventLeptonicTagger);
    RunTagger(hanalysis::HAnalysis::HEventSemiTagger);

//     RunTagger(hanalysis::HAnalysis::HHeavyHiggsHadronicTagger);
//     RunTagger(hanalysis::HAnalysis::HEventHadronicTagger);
    return 1;

}
