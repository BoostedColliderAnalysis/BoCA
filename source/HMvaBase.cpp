# include "HMvaBase.hh"

HMvaBase::HMvaBase()
{

    Print(0, "HMvaBase", "Constructor");

    CutMethodName = "Cut";

    BdtMethodName = "Bdt";

    Cut = "";

    Candidate = new HCandidateBranch();


}

HMvaBase::~HMvaBase()
{

    Print(0, "Destructor");

    delete Candidate;

}


HObservable HMvaBase::NewObservable(float *Value, TString Expression, TString Title, TString Unit)
{

    Print(0, "New Observable", Title);

    HObservable Observable;

    Observable.Value = Value;

    Observable.Expression = Expression;

    Observable.Title = Title;

    Observable.Unit = Unit;

    return Observable;

}

HObservable HMvaBase::NewObservable(float *Value, TString Expression, TString Title)
{
    
    Print(1, "New Observable", Expression);

    HObservable Observable = NewObservable(Value, Expression, Title, "");

    return Observable;

}

HObservable HMvaBase::NewObservable(float *Value, TString Expression)
{

    Print(1, "New Observable", Expression);

    HObservable Observable = NewObservable(Value, Expression, Expression, "");

    return Observable;

}
