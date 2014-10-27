# include "HMva.hh"

hanalysis::HMva::HMva()
{

    Print(1, "HMva", "Constructor");

    CutMethodName = "Cut";

    BdtMethodName = "Bdt";

    Cut = "";

}

hanalysis::HMva::~HMva()
{

    Print(1, "Destructor");

}


HObservable hanalysis::HMva::NewObservable(float *const Value, const string Expression, const string Title, const string Unit, const string Latex) const
{

    Print(1, "New Observable", Title);

    const HObservable Observable(Value, Expression, Title, Unit, Latex);

    return Observable;

}


HObservable hanalysis::HMva::NewObservable(float *const Value, const string Expression, const string Title, const string Unit) const
{

    Print(1, "New Observable", Title);

    const HObservable Observable(Value, Expression, Title, Unit, "");

    return Observable;

}

HObservable hanalysis::HMva::NewObservable(float *const Value, const string Expression, const string Title) const
{

    Print(2, "New Observable", Expression);

    const HObservable Observable = NewObservable(Value, Expression, Title, "", "");

    return Observable;

}

HObservable hanalysis::HMva::NewObservable(float *const Value, const string Expression) const
{

    Print(2, "New Observable", Expression);

    const HObservable Observable = NewObservable(Value, Expression, Expression, "", "");

    return Observable;

}

HObservable::HObservable(float *const NewValue, const string NewExpression, const string NewTitle, const string NewUnit, const string NewLatex)
{

//     Print(1, "Constructor");

    Value = NewValue;

    Expression = NewExpression;

    Title = NewTitle;

    Unit = NewUnit;

    Latex = NewLatex;

}

HObservable::HObservable()
{


}
