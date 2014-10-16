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
    DeltaBaryon2Id(2224),
    NeutronId(2112),
    DeltaBaryonId(1114),
    BMesonSS0Id(533),
    BMesonS0Id(531),
    BMesonSId(523),
    BMesonId(521),
    BMeson0SId(513),
    BMeson0Id(511),
    DMesonS0Id(423),
    DMeson0Id(421),
    DMesonS2Id(415),
    DMesonSId(413),
    DMesonId(411),
    KMesonSId(323),
    KMesonId(321),
    KMeson0SId(313),
    KMeson0Id(311),
    RhoMesonId(213),
    PionId(211),
    IsrId(10),
    OneSigma(0.6827),
    TwoSigma(0.9545),
    ThreeSigma(0.9973)
{

    DebugLevel = 1;
    Print(2, "Constructor");

}

HObject::~HObject()
{

    Print(2, "Destructor");

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

void HObject::Print(const int Severity, const string Description) const
{

    if (Severity <= DebugLevel) {

        Printer(Description);
        std::cout << std::endl;
    }

}


void HObject::Printer(const string Description) const
{

    const char Separator = ' ';
    const int ClassWidth = 28;
    const int FunctionWidth = 25;

    std::cout << std::left << std::setw(ClassWidth) << std::setfill(Separator) << ClassName();
//     cout << left << setw(ClassWidth) << setfill(Separator) << this->n; //  Class_Name();
    std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Description;

}
