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


// HObservable hmva::HMva::NewObservable(float *const Value, const std::string& Expression, const std::string& Title, const std::string& Unit, const std::string& Latex) const
// {
//
//     Print(HNotification, "New Observable", Title);
//
//     const HObservable Observable(Value, Expression, Title, Unit, Latex);
//
//     return Observable;
//
// }
//
//
// HObservable hmva::HMva::NewObservable(float *const Value, const std::string& Expression, const std::string& Title, const std::string& Unit) const
// {
//
//     Print(HNotification, "New Observable", Title);
//
//     const HObservable Observable(Value, Expression, Title, Unit, "");
//
//     return Observable;
//
// }
//
// HObservable hmva::HMva::NewObservable(float *const Value, const std::string& Expression, const std::string& Title) const
// {
//
//     Print(HInformation, "New Observable", Expression);
//
//     const HObservable Observable = NewObservable(Value, Expression, Title, "", "");
//
//     return Observable;
//
// }
//
// HObservable hmva::HMva::NewObservable(float *const Value, const std::string& Expression) const
// {
//
//     Print(HInformation, "New Observable", Expression);
//
//     const HObservable Observable = NewObservable(Value, Expression, Expression, "", "");
//
//     return Observable;
//
// }

// HObservable::HObservable(TValue *const NewValue, const std::string &NewExpression, const std::string &NewTitle, const std::string &NewUnit, const std::string &NewLatex) :
//     Value(NewValue),
//     Expression(NewExpression),
//     Title(NewTitle),
//     Unit(NewUnit),
//     Latex(NewLatex)
// {
// //     Print(HNotification, "Constructor");
// 
// }


