# include "HObject.hh"




hanalysis::HObject::HObject()
{

//     DebugLevel = HNotification;
    DebugLevel = HInformation;
//     DebugLevel = HError;
//     DebugLevel = HDebug;

//     Print(HDebug, "Constructor");

}

hanalysis::HObject::~HObject()
{

//     Print(HDebug, "Destructor");

}

float hanalysis::HObject::GetDistance(const float Rap1, const float Phi1, const float Rap2, const float Phi2) const
{

    Print(HDebug, "GetDistance");

    return (std::sqrt(std::pow((Rap2 - Rap1), 2) + std::pow(GetDeltaPhi(Phi2, Phi1), 2)));

}

float hanalysis::HObject::GetDistance(const float Rap, const float Phi) const
{

    Print(HDebug, "GetDistance");

    return (std::sqrt(std::pow(Rap, 2) + std::pow(Phi, 2)));

}

float hanalysis::HObject::GetDeltaPhi(const float Phi, const float ReferencePhi) const
{

    Print(HDetailed, "GetDeltaPhi");

    float DeltaPhi = Phi - ReferencePhi;

    while (std::abs(DeltaPhi) > Pi) {

        if (DeltaPhi < - Pi) {

            DeltaPhi += TwoPi;

        } else if (DeltaPhi > Pi) {

            DeltaPhi -= TwoPi;

        } else {

            Print(HError, "Get Delta Phi", DeltaPhi);
            break;

        }

    }

    return DeltaPhi;

}
/*

void hanalysis::HObject::Print(const int Severity, const std::string &Description) const
{

    if (Severity <= DebugLevel) {

        Printer(Description);
        std::cout << std::endl;
    }

}



void hanalysis::HObject::Print(HSeverity Severity, const std::string &Description) const
{

  if (Severity <= DebugLevel) {

    Printer(Description);
    std::cout << std::endl;
  }

}*/

void hanalysis::HObject::Printer(const std::string &Description) const
{

    const char Separator = ' ';
    const int NameSpaceWidth = 12;
    const int ClassWidth = 21;
    const int FunctionWidth = 25;

    std::cout << std::left << std::setw(NameSpaceWidth) << std::setfill(Separator) << NameSpaceName();
    std::cout << std::left << std::setw(ClassWidth) << std::setfill(Separator) << ClassName();
//     cout << left << setw(ClassWidth) << setfill(Separator) << this->n; //  Class_Name();
    std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Description;

}

std::string hanalysis::HObject::GetParticleName(const int ParticleId) const
{

    std::string Sign = "";
    if (ParticleId < 0) Sign = "-";

    switch (std::abs(ParticleId)) {
//     case EmptyId: return (Sign + "Empty");
    case DownId:
        return (Sign + "d");
    case UpId:
        return (Sign + "u");
    case StrangeId:
        return (Sign + "s");
    case CharmId:
        return (Sign + "c");
    case BottomId:
        return (Sign + "b");
    case TopId:
        return (Sign + "t");
    case ElectronId:
        return (Sign + "e");
    case ElectronNeutrinoId:
        return (Sign + "nue");
    case MuonId:
        return (Sign + "mu");
    case MuonNeutrinoId:
        return (Sign + "numu");
    case TauLeptonId:
        return (Sign + "tau");
    case TauNeutrinoId:
        return (Sign + "nutau");
    case GluonId:
        return (Sign + "g");
    case PhotonId:
        return (Sign + "gamma");
    case ZId:
        return (Sign + "Z");
    case WId:
        return (Sign + "W");
    case HiggsId:
        return (Sign + "h");
    case HeavyHiggsId:
        return (Sign + "H");
    case IsrId:
        return (Sign + "ISR");
    case MarkerId:
        return (Sign + "TEMP");
    case ClusterId:
        return (Sign + "Cluster");
    case StringId:
        return (Sign + "String");
    case MixedJetId:
        return (Sign + "MixJet");
    case Pi0MesonId:
        return (Sign + "pi0");
    case Rho0MesonId:
        return (Sign + "rho0");
    case K0LMesonId:
        return (Sign + "K0l");
    case PionId:
        return (Sign + "pi");
    case RhoMesonId:
        return (Sign + "rho");
    case RapMesonId:
        return (Sign + "eta");
    case OmegaMesonId:
        return (Sign + "omega");
    case K0SMesonId:
        return (Sign + "K0s");
    case KMeson0Id:
        return (Sign + "K0");
    case KMeson0SId:
        return (Sign + "K0*");
    case KMesonId:
        return (Sign + "K");
    case KMesonSId:
        return (Sign + "K*");
    case RapPMesonId:
        return (Sign + "etaP");
    case DMesonId:
        return (Sign + "D");
    case DMesonSId:
        return (Sign + "D*");
    case DMesonS2Id:
        return (Sign + "D*2");
    case DMeson0Id:
        return (Sign + "D0");
    case DMesonS0Id:
        return (Sign + "D*0");
    case RapCMesonId:
        return (Sign + "etac");
    case BMeson0Id:
        return (Sign + "B0");
    case BMeson0SId:
        return (Sign + "B0*");
    case BMesonId:
        return (Sign + "B");
    case BMesonSId:
        return (Sign + "B*");
    case BMesonS0Id:
        return (Sign + "B*0");
    case BMesonSS0Id:
        return (Sign + "Bs*0");
    case DownDown1Id:
        return (Sign + "dd1");
    case UpDown0Id:
        return (Sign + "ud0");
    case UpDown1Id:
        return (Sign + "ud1");
    case DeltaBaryonId:
        return (Sign + "Delta");
    case NeutronId:
        return (Sign + "n");
    case UpUp1Id:
        return (Sign + "uu1");
    case ProtonId:
        return (Sign + "p");
    case DeltaBaryon2Id:
        return (Sign + "Delta2");
    case CpvHiggsId:
        return (Sign + "h");
    default:
        return std::to_string(ParticleId);
    }

}


float hanalysis::HObject::GetParticleMass(const HParticleId ParticleId) const
{

    switch (std::abs(ParticleId)) {
    case StrangeId:
        return 0.095;
    case CharmId:
        return 1.28;
    case BottomId:
        return 4.18;
    case TopId:
        return TopMass;
    case ElectronId:
        return ElectronMass;
    case ElectronNeutrinoId:
        return NeutrinoMass;
    case MuonId:
        return MuonMass;
    case MuonNeutrinoId:
        return NeutrinoMass;
    case TauLeptonId:
        return TauMass;
    case TauNeutrinoId:
        return NeutrinoMass;
    case ZId:
        return ZMass;
    case WId:
        return WMass;
    case HiggsId:
        return HiggsMass;
    case Pi0MesonId:
        return 0.13498;
//         case Rho0MesonId:
//             return (Sign + "rho0");
//         case K0LMesonId:
//             return (Sign + "K0l");
    case PionId:
        return 0.13957;
    case RhoMesonId:
        return 0.77549;
    case RapMesonId:
        return 0.54785;
    case OmegaMesonId:
        return 0.78265;
//         case K0SMesonId:
//             return (Sign + "K0s");
//         case KMeson0Id:
//             return (Sign + "K0");
//         case KMeson0SId:
//             return (Sign + "K0*");
//         case KMesonId:
//             return (Sign + "K");
//         case KMesonSId:
//             return (Sign + "K*");
//         case RapPMesonId:
//             return (Sign + "etaP");
//         case DMesonId:
//             return (Sign + "D");
//         case DMesonSId:
//             return (Sign + "D*");
//         case DMesonS2Id:
//             return (Sign + "D*2");
//         case DMeson0Id:
//             return (Sign + "D0");
//         case DMesonS0Id:
//             return (Sign + "D*0");
//         case RapCMesonId:
//             return (Sign + "etac");
//         case BMeson0Id:
//             return (Sign + "B0");
//         case BMeson0SId:
//             return (Sign + "B0*");
//         case BMesonId:
//             return (Sign + "B");
//         case BMesonSId:
//             return (Sign + "B*");
//         case BMesonS0Id:
//             return (Sign + "B*0");
//         case BMesonSS0Id:
//             return (Sign + "Bs*0");
//         case DownDown1Id:
//             return (Sign + "dd1");
//         case UpDown0Id:
//             return (Sign + "ud0");
//         case UpDown1Id:
//             return (Sign + "ud1");
//         case DeltaBaryonId:
//             return (Sign + "Delta");
    case NeutronId:
        return 1.00866;
//         case UpUp1Id:
//             return (Sign + "uu1");
    case ProtonId:
        return 0.93827;
//         case DeltaBaryon2Id:
//             return (Sign + "Delta2");
    case CpvHiggsId:
        return HiggsMass;
    default:
        return 0;
    }

}

