# include "Object.hh"

namespace analysis
{

Object::Object()
{
//   debug_level_ = kInformation;
    debug_level_ = kNotification;
    //     debug_level_ = kError;
    //     debug_level_ = kDebug;
//     Print(kDebug, "Constructor");
}

void Object::Printer(const std::string &Description, const std::string &func) const
{
    const char Separator = ' ';
    const int NameSpaceWidth = 12;
    const int ClassWidth = 21;
    const int FunctionWidth = 25;
    std::cout << std::left << std::setw(NameSpaceWidth) << std::setfill(Separator) << NameSpaceName();
    std::cout << std::left << std::setw(ClassWidth) << std::setfill(Separator) << ClassName();
//     std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << func;
//     cout << left << setw(ClassWidth) << setfill(Separator) << this->n; //  Class_Name();
    std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Description;
}

std::string Object::Name(const int particle_id) const
{
    std::string sign = "";
    if (particle_id < 0) sign = "-";
    switch (std::abs(particle_id)) {
//     case EmptyId: return (Sign + "Empty");
    case DownId:
        return (sign + "d");
    case UpId:
        return (sign + "u");
    case StrangeId:
        return (sign + "s");
    case CharmId:
        return (sign + "c");
    case BottomId:
        return (sign + "b");
    case TopId:
        return (sign + "t");
    case ElectronId:
        return (sign + "e");
    case ElectronNeutrinoId:
        return (sign + "nue");
    case MuonId:
        return (sign + "mu");
    case MuonNeutrinoId:
        return (sign + "numu");
    case TauId:
        return (sign + "tau");
    case TauNeutrinoId:
        return (sign + "nutau");
    case GluonId:
        return (sign + "g");
    case PhotonId:
        return (sign + "gamma");
    case ZId:
        return (sign + "Z");
    case WId:
        return (sign + "W");
    case HiggsId:
        return (sign + "h");
    case HeavyHiggsId:
        return (sign + "H");
    case ChargedHiggsId:
        return (sign + "H+");
    case IsrId:
        return (sign + "ISR");
    case MarkerId:
        return (sign + "TEMP");
    case ClusterId:
        return (sign + "Cluster");
    case StringId:
        return (sign + "String");
    case MixedJetId:
        return (sign + "MixJet");
    case Pi0MesonId:
        return (sign + "pi0");
    case Rho0MesonId:
        return (sign + "rho0");
    case K0LMesonId:
        return (sign + "K0l");
    case PionId:
        return (sign + "pi");
    case RhoMesonId:
        return (sign + "rho");
    case RapMesonId:
        return (sign + "eta");
    case OmegaMesonId:
        return (sign + "omega");
    case K0SMesonId:
        return (sign + "K0s");
    case KMeson0Id:
        return (sign + "K0");
    case KMeson0SId:
        return (sign + "K0*");
    case KMesonId:
        return (sign + "K");
    case KMesonSId:
        return (sign + "K*");
    case RapPMesonId:
        return (sign + "etaP");
    case DMesonId:
        return (sign + "D");
    case DMesonSId:
        return (sign + "D*");
    case DMesonS2Id:
        return (sign + "D*2");
    case DMeson0Id:
        return (sign + "D0");
    case DMesonS0Id:
        return (sign + "D*0");
    case RapCMesonId:
        return (sign + "etac");
    case BMeson0Id:
        return (sign + "B0");
    case BMeson0SId:
        return (sign + "B0*");
    case BMesonId:
        return (sign + "B");
    case BMesonSId:
        return (sign + "B*");
    case BMesonS0Id:
        return (sign + "B*0");
    case BMesonSS0Id:
        return (sign + "Bs*0");
    case DownDown1Id:
        return (sign + "dd1");
    case UpDown0Id:
        return (sign + "ud0");
    case UpDown1Id:
        return (sign + "ud1");
    case DeltaBaryonId:
        return (sign + "Delta");
    case NeutronId:
        return (sign + "n");
    case UpUp1Id:
        return (sign + "uu1");
    case ProtonId:
        return (sign + "p");
    case DeltaBaryon2Id:
        return (sign + "Delta2");
    case CpvHiggsId:
        return (sign + "h");
    default:
        return std::to_string(particle_id);
    }
}

float Object::Mass(const ParticleId particle_id) const
{
    switch (std::abs(particle_id)) {
    case StrangeId:
        return 0.095;
    case CharmId:
        return 1.28;
    case BottomId:
        return 4.18;
    case TopId:
        return 173.5;
    case ElectronId:
        return 0.000511;
    case ElectronNeutrinoId:
        return 0;
    case MuonId:
        return 0.1134;
    case MuonNeutrinoId:
        return 0;
    case TauId:
        return 1.776;
    case TauNeutrinoId:
        return 0;
    case PhotonId:
        return 0;
    case ZId:
        return 91.188;
    case WId:
        return 80.39;
    case HiggsId:
        return 125;
    case Pi0MesonId:
        return 0.13498;
    case PionId:
        return 0.13957;
    case RhoMesonId:
        return 0.77549;
    case RapMesonId:
        return 0.54785;
    case OmegaMesonId:
        return 0.78265;
    case NeutronId:
        return 1.00866;
    case ProtonId:
        return 0.93827;
    case CpvHiggsId:
        return Mass(HiggsId);
    default:
        return 0;
    }
}

}
