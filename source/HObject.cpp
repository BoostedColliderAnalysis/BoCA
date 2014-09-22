# include "HObject.hh"

HObject::HObject() :
    LargeNumber(999999999),
    HiggsMass(125),
    TopMass(173.5),
    WMass(80.39),
    MuonMass(0.1134),
    ElectronMass(0.000511),
    HiggsUserIndex(1000),
    TopUserIndex(2000),
    TopId(6),
    BottomId(5),
    EmptyId(-1)
{

    Print(0, "Constructor");

    Debug = 5;

}

HObject::~HObject()
{

    Print(0, "Destructor");

}

float HObject::GetDistance(float Eta1, float Phi1, float Eta2, float Phi2)
{

    Print(2, "GetDistance");

    float Distance = sqrt(pow((Eta2 - Eta1), 2) + pow(GetDeltaPhi(Phi2, Phi1), 2));

    return (Distance);

}


float HObject::GetDistance(float Eta, float Phi)
{

    Print(2, "GetDistance");

    float Distance = sqrt(pow(Eta, 2) + pow(Phi, 2));

    return (Distance);

}

float HObject::GetDeltaPhi(float Phi, float RefPhi)
{

    Print(3, "GetDeltaPhi");

    const float TwoPi = 2 * Pi();

    float DeltaPhi = Phi - RefPhi;

    while (fabs(DeltaPhi) > Pi()) {

        if (DeltaPhi < -Pi()) {

            DeltaPhi += TwoPi;

        } else if (DeltaPhi > Pi()) {

            DeltaPhi -= TwoPi;

        }

    }

    return (DeltaPhi);

}


void HObject::Print(int debug, TString Function)
{

    if (debug < Debug) {

        Printer(Function);
        cout << endl;
    }

}


void HObject::Printer(TString Function)
{

    const char Separator = ' ';
    const int ClassWidth = 28;
    const int FunctionWidth = 25;

    cout << left << setw(ClassWidth) << setfill(Separator) << ClassName();
    cout << left << setw(FunctionWidth) << setfill(Separator) << Function;

}
