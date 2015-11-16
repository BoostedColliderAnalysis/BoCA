#pragma once

#include "AnalysisHeavyHiggs.hh"

namespace boca
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

    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::Htb);
            break;
        case Tag::background :
            this->NewFile(tag, Process::tt);
            break;
        }
    }

//     std::string ProcessName() const {
//         return "Charged";
//     }

    std::string AnalysisName() const final {
      return  "Charged-" + Name(this->collider_type()) + "-" + boca::Name(this->PreCut()) + "-" + boca::Name(this->Mass());
    }

private:

    Crosssection SignalCrosssection() const {
        switch (this->collider_type()) {
        case Collider::LHC:
            switch (this->Mass()) {
            case 500 : return 3.0495761279999996 * pb;
            case 1000 : return 0.22623192864 * pb;
            case 2000 : return 0.005720855039999999 * pb;
            case 3000 : return 0.0003035467008 * pb;
            case 4000 : return 0.000020556093312 * pb;
            default:
//                 Error("Signal Crosssection", "unhandled case");
                return pb;
            } ;
        case Collider::LE:
            switch (this->Mass()) {
            case 500 : return 247.86995327999998 * pb;
            case 700 : return 109.26120959999999 * pb;
            case 1000 : return 39.81212064 * pb;
            case 1500 : return 10.639675008 * pb;
            case 2000 : return 3.8189750399999998 * pb;
            case 3000 : return 0.7737415487999998 * pb;
            case 4000 : return 0.22421177856 * pb;
            case 5000 : return 0.07985005056 * pb;
            case 6000 : return 0.03297554496 * pb;
            case 8000 : return 0.007364981375999998 * pb;
            case 10000 : return 0.0020553163775999996 * pb;
            case 12000 : return 0.0006632091647999999 * pb;
            case 15000 : return 0.00014951794176 * pb;
            case 20000 : return 0.000016388469792 * pb;
            default:
//                 Error("Signal Crosssection", "unhandled case");
                return pb;
            }
        default:
//             Error("Signal Crosssection", "unhandled case");
            return pb;
        }
    }

    int PassPreCut(Event const& event, Tag) const {
//         Info("pass pre cut");
        Jets Particles = event.Partons().GenParticles();
        Jets Quarks = fastjet::sorted_by_pt(CopyIf5Quark(Particles));
        Quarks = fastjet::sorted_by_pt(RemoveIfMother(Quarks, Id::top));
        if (Quarks.empty()) {
            //       if (Tag == Tag::signal && PreCut() > 0 && !(Tagger == BottomTagger || Tagger == HBottomReader))
            //       if (PreCut() > 0)
//             Error("Not enough bottom quarks", Quarks.size());
            return 0;
        } else if (Quarks.front().pt() < to_float(this->PreCut()))
            return 0;
        Jets TopQuarks = fastjet::sorted_by_pt(CopyIfParticle(Particles, Id::top));
        if (TopQuarks.size() != 2) {
//             Error("Not enough top quarks", TopQuarks.size());
            return 0;
        } else if (TopQuarks.front().pt() < to_float(this->PreCut()))
            return 0;
        if (event.Hadrons().MissingEt().pt() < to_float(this->MissingEt()))
            return 0;
        Jets Leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
        if (Leptons.empty())
            return 0;
        if (Leptons.front().pt() < to_float(this->LeptonPt()))
            return 0;
        Jets jets = event.Hadrons().Jets();
        if (jets.size() < 4)
            return 0;
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

    Crosssection BackgroundCrosssection(Process) const {
        switch (this->collider_type()) {
        case Collider::LHC :
            switch (this->PreCut()) {
            case 0 : return 97.54 * 2 * pb;
            case 250 : return 4.206 * 2 * pb;
            }
        case Collider::LE: {
            switch (this->PreCut()) {
            case 0 : return 3564. * 2 * pb;
            case 300 : return 187.3 * 2 * pb;
            case 1500 : return 0.447 * 2 * pb;
            case 2500 : return 0.0442 * 2 * pb;
            }
        }
        default :
//             Error("unhandled case");
            return pb;
        }
    }

};

}

}
