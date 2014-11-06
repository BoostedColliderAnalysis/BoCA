# include "HObject.hh"

hanalysis::HObject::HObject() :
    LargeNumber(999999999),
    TopMass(173.5),
    HiggsMass(125),
    WMass(80.39),
    TauMass(1.776),
    MuonMass(0.1134),
    ElectronMass(0.000511),
    EmptyUserIndex(-1),
    EmptyPosition(-1),
    OneSigma(0.6827),
    TwoSigma(0.9545),
    ThreeSigma(0.9973)
{

    DebugLevel = 1;
    Print(3, "Constructor");

}

hanalysis::HObject::~HObject()
{

    Print(3, "Destructor");

}

float hanalysis::HObject::GetDistance(const float Eta1, const float Phi1, const float Eta2, const float Phi2) const
{

    Print(3, "GetDistance");

    return( sqrt(pow((Eta2 - Eta1), 2) + pow(GetDeltaPhi(Phi2, Phi1), 2)));

}

float hanalysis::HObject::GetDistance(const float Eta, const float Phi) const
{

    Print(3, "GetDistance");

    return (sqrt(pow(Eta, 2) + pow(Phi, 2)));

}

float hanalysis::HObject::GetDeltaPhi(const float Phi, const float RefPhi) const
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

void hanalysis::HObject::Print(const int Severity, const string& Description) const
{

    if (Severity <= DebugLevel) {

        Printer(Description);
        std::cout << std::endl;
    }

}


void hanalysis::HObject::Printer(const string& Description) const
{

    const char Separator = ' ';
    const int NameSpaceWidth = 12;
    const int ClassWidth = 17;
    const int FunctionWidth = 25;

    std::cout << std::left << std::setw(NameSpaceWidth) << std::setfill(Separator) << NameSpaceName();
    std::cout << std::left << std::setw(ClassWidth) << std::setfill(Separator) << ClassName();
//     cout << left << setw(ClassWidth) << setfill(Separator) << this->n; //  Class_Name();
    std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Description;

}

string hanalysis::HObject::GetParticleName(const int ParticleId) const {

  string Sign = "";
  if (ParticleId < 0) Sign = "-";

  switch (abs(ParticleId)) {
//     case EmptyId: return (Sign + "Empty");
    case DownId: return (Sign + "d");
    case UpId: return (Sign + "u");
    case StrangeId: return (Sign + "s");
    case CharmId: return (Sign + "c");
    case BottomId: return (Sign + "b");
    case TopId: return (Sign + "t");
    case ElectronId: return (Sign + "e");
    case ElectronNeutrinoId: return (Sign + "nue");
    case MuonId: return (Sign + "mu");
    case MuonNeutrinoId: return (Sign + "numu");
    case TauLeptonId: return (Sign + "tau");
    case TauNeutrinoId: return (Sign + "nutau");
    case GluonId: return (Sign + "g");
    case PhotonId: return (Sign + "gamma");
    case ZId: return (Sign + "Z");
    case WId: return (Sign + "W");
    case HiggsId: return (Sign + "h");
    case HeavyHiggsId: return (Sign + "H");
    case IsrId: return (Sign + "ISR");
    case MarkerId: return (Sign + "TEMP");
    case ClusterId: return (Sign + "Cluster");
    case StringId: return (Sign + "String");
    case Pi0MesonId: return (Sign + "pi0");
    case Rho0MesonId: return (Sign + "rho0");
    case K0LMesonId: return (Sign + "K0l");
    case PionId: return (Sign + "pi");
    case RhoMesonId: return (Sign + "rho");
    case EtaMesonId: return (Sign + "eta");
    case OmegaMesonId: return (Sign + "omega");
    case K0SMesonId: return (Sign + "K0s");
    case KMeson0Id: return (Sign + "K0");
    case KMeson0SId: return (Sign + "K0*");
    case KMesonId: return (Sign + "K");
    case KMesonSId: return (Sign + "K*");
    case EtaPMesonId: return (Sign + "etaP");
    case DMesonId: return (Sign + "D");
    case DMesonSId: return (Sign + "D*");
    case DMesonS2Id: return (Sign + "D*2");
    case DMeson0Id: return (Sign + "D0");
    case DMesonS0Id: return (Sign + "D*0");
    case EtaCMesonId: return (Sign + "etac");
    case BMeson0Id: return (Sign + "B0");
    case BMeson0SId: return (Sign + "B0*");
    case BMesonId: return (Sign + "B");
    case BMesonSId: return (Sign + "B*");
    case BMesonS0Id: return (Sign + "B*0");
    case BMesonSS0Id: return (Sign + "Bs*0");
    case DownDown1Id: return (Sign + "dd1");
    case UpDown0Id: return (Sign + "ud0");
    case UpDown1Id: return (Sign + "ud1");
    case DeltaBaryonId: return (Sign + "Delta");
    case NeutronId: return (Sign + "n");
    case UpUp1Id: return (Sign + "uu1");
    case ProtonId: return (Sign + "p");
    case DeltaBaryon2Id: return (Sign + "Delta2");
    case CpvHiggsId: return (Sign + "h");
    default: return std::to_string(ParticleId);
  }

}
