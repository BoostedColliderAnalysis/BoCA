# include "HObject.hh"

HObject::HObject() :
    LargeNumber(999999999),
    TopMass(173.5),
    HiggsMass(125),
    WMass(80.39),
    TauMass(1.776),
    MuonMass(0.1134),
    ElectronMass(0.000511),
    HiggsUserIndex(1000),
    TopUserIndex(2000),
    EmptyUserIndex(-1),
    CpvHiggsId(5000000),
    ProtonId(2212),
    UpUp1Id(2203),
    UpDown1Id(2103),
    UpDown0Id(2101),
    DownDown1Id(1103),
    HeavyHiggsId(35),
    GluonId(21),
    MuonId(13),
    ElectronId(11),
    TopId(6),
    BottomId(5),
    CharmId(4),
    StrangeId(3),
    UpId(2),
    DownId(1),
    EmptyId(0),
    IsrId(10),
    Undefined(3),
    Unstable(2),
    Stable(1)
{

//     Print(1, "Constructor");

    DebugLevel = 0;

}

HObject::~HObject()
{

    Print(1, "Destructor");

}

float HObject::GetDistance(const float Eta1, const float Phi1, const float Eta2, const float Phi2) const
{

    Print(3, "GetDistance");

    float const Distance = sqrt(pow((Eta2 - Eta1), 2) + pow(GetDeltaPhi(Phi2, Phi1), 2));

    return Distance;

}

float HObject::GetDistance(const float Eta, const float Phi) const
{

    Print(3, "GetDistance");

    float const Distance = sqrt(pow(Eta, 2) + pow(Phi, 2));

    return Distance;

}

float HObject::GetDeltaPhi(const float Phi, const float RefPhi) const
{

    Print(4, "GetDeltaPhi");

    float const TwoPi = 2 * TMath::Pi();

    float DeltaPhi = Phi - RefPhi;


    while (fabs(DeltaPhi) > TMath::Pi()) {

        if (DeltaPhi < -float(TMath::Pi())) {

            DeltaPhi += TwoPi;

        } else if (DeltaPhi > float(TMath::Pi())) {

            DeltaPhi -= TwoPi;

        } else {

            break;

        }

    }

    return DeltaPhi;

}

void HObject::Print(const int Severity, const string Function) const
{

    if (Severity <= DebugLevel) {

        Printer(Function);
        std::cout << std::endl;
    }

}


void HObject::Printer(const string Function) const
{

    const char Separator = ' ';
    const int ClassWidth = 28;
    const int FunctionWidth = 25;

    std::cout << std::left << std::setw(ClassWidth) << std::setfill(Separator) << ClassName();
//     cout << left << setw(ClassWidth) << setfill(Separator) << this->n; //  Class_Name();
    std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Function;

}
