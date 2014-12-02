# include "HMva.hh"

hanalysis::HMva::HMva()
{

    Print(HNotification, "HMva", "Constructor");

    CutMethodName = "Cut";

    BdtMethodName = "Bdt";

    Cut = "";

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
