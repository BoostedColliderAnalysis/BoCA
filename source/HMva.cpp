# include "HMva.hh"

hanalysis::HMva::HMva()
{
    Print(HNotification, "Constructor");
    CutMethodName = "Cut";
    BdtMethodName = "Bdt";
    Cut = "";
    WeightBranchName = "Info";
    MaxCombi = 4;
}

hanalysis::HMva::~HMva()
{

    Print(HNotification, "Destructor");

}

float hanalysis::HMva::GetBdt(TObject *, TMVA::Reader *)
{

    Print(HError, "Get Bdt", "should be implemented somewhere else");

    return 0;

}
