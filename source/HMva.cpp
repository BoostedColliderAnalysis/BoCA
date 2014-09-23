# include "HMva.hh"

HMva::HMva()
{

    Print(0, "HMva", "Constructor");

    CutMethodName = "Cut";

    BdtMethodName = "Bdt";

    Cut = "";

}

HMva::~HMva()
{

    Print(0, "Destructor");

}


HObservable HMva::NewObservable(float *Value, TString Expression, TString Title, TString Unit)
{

    Print(0, "New Observable", Title);

    HObservable Observable;

    Observable.Value = Value;

    Observable.Expression = Expression;

    Observable.Title = Title;

    Observable.Unit = Unit;

    return Observable;

}

HObservable HMva::NewObservable(float *Value, TString Expression, TString Title)
{
    
    Print(1, "New Observable", Expression);

    HObservable Observable = NewObservable(Value, Expression, Title, "");

    return Observable;

}

HObservable HMva::NewObservable(float *Value, TString Expression)
{

    Print(1, "New Observable", Expression);

    HObservable Observable = NewObservable(Value, Expression, Expression, "");

    return Observable;

}
