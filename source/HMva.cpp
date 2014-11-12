# include "HMva.hh"

hmva::HMva::HMva()
{

    Print(1, "HMva", "Constructor");

    CutMethodName = "Cut";

    BdtMethodName = "Bdt";

    Cut = "";

}

hmva::HMva::~HMva()
{

    Print(1, "Destructor");

}


HObservable hmva::HMva::NewObservable(float *const Value, const std::string& Expression, const std::string& Title, const std::string& Unit, const std::string& Latex) const
{

    Print(1, "New Observable", Title);

    const HObservable Observable(Value, Expression, Title, Unit, Latex);

    return Observable;

}


HObservable hmva::HMva::NewObservable(float *const Value, const std::string& Expression, const std::string& Title, const std::string& Unit) const
{

    Print(1, "New Observable", Title);

    const HObservable Observable(Value, Expression, Title, Unit, "");

    return Observable;

}

HObservable hmva::HMva::NewObservable(float *const Value, const std::string& Expression, const std::string& Title) const
{

    Print(2, "New Observable", Expression);

    const HObservable Observable = NewObservable(Value, Expression, Title, "", "");

    return Observable;

}

HObservable hmva::HMva::NewObservable(float *const Value, const std::string& Expression) const
{

    Print(2, "New Observable", Expression);

    const HObservable Observable = NewObservable(Value, Expression, Expression, "", "");

    return Observable;

}

HObservable::HObservable(float *const NewValue, const std::string& NewExpression, const std::string& NewTitle, const std::string& NewUnit, const std::string& NewLatex)
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
