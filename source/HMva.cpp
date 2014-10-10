# include "HMva.hh"

HMva::HMva()
{

    Print(1, "HMva", "Constructor");

    CutMethodName = "Cut";

    BdtMethodName = "Bdt";

    Cut = "";

}

HMva::~HMva()
{

    Print(1, "Destructor");

}


HObservable HMva::NewObservable(float *Value, const string Expression, const string Title, const string Unit)
{

    Print(1, "New Observable", Title);

    HObservable Observable(Value,Expression,Title,Unit);

    return Observable;

}

HObservable HMva::NewObservable(float *Value, const string Expression, const string Title)
{

    Print(2, "New Observable", Expression);

    HObservable Observable = NewObservable(Value, Expression, Title, "");

    return Observable;

}

HObservable HMva::NewObservable(float *Value, const string Expression)
{

    Print(2, "New Observable", Expression);

    HObservable Observable = NewObservable(Value, Expression, Expression, "");

    return Observable;

}

HObservable::HObservable(float *NewValue, const string NewExpression, const string NewTitle, const string NewUnit)
{
    
//     Print(1, "Constructor");
    
    Value = NewValue;
    
    Expression = NewExpression;
    
    Title = NewTitle;
    
    Unit = NewUnit;
    
}

HObservable::HObservable()
{
    
    
}
