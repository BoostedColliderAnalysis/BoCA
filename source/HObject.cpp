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
    HeavyHiggsId(26),
    GluonId(21),
    TopId(6),
    BottomId(5),
    CharmId(4),
    StrangeId(3),
    UpId(2),
    DownId(1),
    EmptyId(0),
    IsrId(10)
{

//     Print(0, "Constructor");

    Debug = 0;

}

HObject::~HObject()
{

    Print(0, "Destructor");

}

float HObject::GetDistance(float Eta1, float Phi1, float Eta2, float Phi2) const
{

    Print(2, "GetDistance");

    float const Distance = sqrt(pow((Eta2 - Eta1), 2) + pow(GetDeltaPhi(Phi2, Phi1), 2));

    return Distance;

}

float HObject::GetDistance(float Eta, float Phi) const
{

    Print(2, "GetDistance");

    float const Distance = sqrt(pow(Eta, 2) + pow(Phi, 2));

    return Distance;

}

float HObject::GetDeltaPhi(float Phi, float RefPhi) const
{

    Print(3, "GetDeltaPhi");

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

void HObject::Print(int debug, string Function) const
{

    if (debug < Debug) {

        Printer(Function);
        std::cout << std::endl;
    }

}


void HObject::Printer(string Function) const
{

    char const Separator = ' ';
    int const ClassWidth = 28;
    int const FunctionWidth = 25;

    std::cout << std::left << std::setw(ClassWidth) << std::setfill(Separator) << ClassName();
//     cout << left << setw(ClassWidth) << setfill(Separator) << this->n; //  Class_Name();
    std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Function;

}


PseudoJet HObject::GetPseudoJet(TLorentzVector Vector) const
{

    PseudoJet const Jet(Vector.Px(), Vector.Py(), Vector.Pz(), Vector.E());

    return Jet;

}


