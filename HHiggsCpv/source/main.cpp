#include "HAnalysisHiggsCpv.hh"

int main()
{
    hhiggscpv::HAnalysis *Analysis = new hhiggscpv::HAnalysis();
    
//     if (!gSystem->AccessPathName( Analysis->GetProje )) {
//         // first we try to find the file in the local directory
//         std::cout << "--- TMVAMulticlass   : Accessing " << fname << std::endl;
//         input = TFile::Open( fname );
//     }

//     Analysis->AnalysisLoop("BTagger");
// 
//     hmva::HMva *Mva = new hhiggscpv::HMvaBTagger();
// 
//     hmva::HFactory *Factory = new hmva::HFactory(Mva);
// 
//     delete Factory;
// 
//     delete Mva;

    Analysis->AnalysisLoop("Event");

    delete Analysis;

    return 1;

}
