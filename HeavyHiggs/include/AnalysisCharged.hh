#pragma once

#include "AnalysisHeavyHiggs.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisCharged : public AnalysisHeavyHiggs<Tagger>
{

public:

    AnalysisCharged() {
        this->tagger().set_analysis_name(ProjectName());
    }

    void SetFiles(const Tag tag) {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::Htb);
            break;
        case Tag::background :
            this->NewFile(tag, Process::tt);
            break;
        }
    }

    std::string ProcessName()const {
        return "Charged";
    }

    std::string ProjectName() const {
        return  ProcessName() + "-" + Name(this->collider_type()) + "-" + std::to_string(this->PreCut()) + "GeV-" + std::to_string(this->Mass()) + "GeV";
    }

private:

    float SignalCrosssection() const {
        switch (this->collider_type()) {
        case Collider::LHC:
            switch (this->Mass()) {
            case 500:
                return 3.0495761279999996;
            case 1000:
                return 0.22623192864;
            case 2000:
                return 0.005720855039999999;
            case 3000:
                return 0.0003035467008;
            case 4000:
                return 0.000020556093312;
            default:
//                 Error("Signal Crosssection", "unhandled case");
                return 1;
            } ;
        case Collider::LE:
            switch (this->Mass()) {
            case 500:
                return 247.86995327999998;
            case 700:
                return 109.26120959999999;
            case 1000:
                return 39.81212064;
            case 1500:
                return 10.639675008;
            case 2000:
                return 3.8189750399999998;
            case 3000:
                return 0.7737415487999998;
            case 4000:
                return 0.22421177856;
            case 5000:
                return 0.07985005056;
            case 6000:
                return 0.03297554496;
            case 8000:
                return 0.007364981375999998;
            case 10000:
                return 0.0020553163775999996;
            case 12000:
                return 0.0006632091647999999;
            case 15000:
                return 0.00014951794176;
            case 20000:
                return 0.000016388469792;
            default:
//                 Error("Signal Crosssection", "unhandled case");
                return 1;
            }
        default:
//             Error("Signal Crosssection", "unhandled case");
            return 1;
        }
    }

    int PassPreCut(const Event &event) {
//         Info("pass pre cut");
        Jets Particles = event.Partons().GenParticles();
        Jets Quarks = fastjet::sorted_by_pt(RemoveIfNot5Quarks(Particles));
        Quarks = fastjet::sorted_by_pt(RemoveIfAbsMother(Quarks, Id::top));
        if (Quarks.empty()) {
            //       if (Tag == Tag::signal && PreCut() > 0 && !(Tagger == BottomTagger || Tagger == HBottomReader))
            //       if (PreCut() > 0)
//             Error("Not enough bottom quarks", Quarks.size());
            return 0;
        } else if (Quarks.front().pt() < this->PreCut()) return 0;


        Jets TopQuarks = fastjet::sorted_by_pt(RemoveIfWrongAbsParticle(Particles, Id::top));
        if (TopQuarks.size() != 2) {
//             Error("Not enough top quarks", TopQuarks.size());
            return 0;
        } else if (TopQuarks.front().pt() < this->PreCut()) return 0;


        if (event.Hadrons().MissingEt().pt() < this->MissingEt()) return 0;
        Jets Leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
        if (Leptons.empty()) return 0;
        if (Leptons.front().pt() < this->LeptonPt()) return 0;
        Jets jets = event.Hadrons().Jets();
        if (jets.size() < 4) return 0;
        return 1;
    }
    int BackgroundFileNumber() const {
        switch (this->collider_type()) {
        case Collider::LHC :
            switch (this->PreCut()) {
            case 0 :
                //                 return 1;
                return 79; // < should be switched on
            case 250 :
                return 58; // < should be switched on
            default :
                return 1;
            }
        case Collider::LE :
            switch (this->PreCut()) {
            case 2500 :
                return 28;
            case 2000 :
                return 16;
            case 1500 :
                return 19;
            case 300 :
                return 61; // < should be switched on
                //                 return 1;
            case 0 :
                return 118; // < should be switched on
                //                 return 1;
            default :
                return 1;
            }
        default :
            return 1;
        }
    }

    float BackgroundCrosssection(const Process process) const {
        switch (this->collider_type()) {
        case Collider::LHC :
            switch (this->PreCut()) {
            case 0 :
                return 97.54 * 2 * 1000;
            case 250 :
                return 4.206 * 2 * 1000;
            }
        case Collider::LE: {
            switch (this->PreCut()) {
            case 0 :
                return 3564 * 2 * 1000;
            case 300 :
                return 187.3 * 2 * 1000;
            case 1500 :
                return 0.447 * 2 * 1000;
            case 2500 :
                return 0.0442 * 2 * 1000;
            }
        }
        default :
//             Error("unhandled case");
            return 1;
        }
    }

};

}

}
