# include "HMva.hh"

hmva::HMva::HMva()
{

    Print(HNotification, "HMva", "Constructor");

    CutMethodName = "Cut";

    BdtMethodName = "Bdt";

    Cut = "";

}

hmva::HMva::~HMva()
{

    Print(HNotification, "Destructor");

}

float hmva::HMva::GetBdt(TObject *, TMVA::Reader *)
{

    Print(HError, "Get Bdt", "should be implemented somewhere else");

    return 0;
}
