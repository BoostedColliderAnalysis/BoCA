#pragma once

#include "AnalysisHeavyHiggs.hh"
#include "Sort.hh"
#include "Vector.hh"

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

    void SetFiles(Tag tag, Stage)override {
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

    std::string AnalysisName() const override {
        return  "Charged-" + Name(this->Collider()) + "-" + boca::Name(this->PreCut()) + "-" + boca::Name(this->Mass());
    }

private:

    Crosssection SignalCrosssection() const {
        switch (this->Collider()) {
        case heavyhiggs::Collider::LHC:
            switch (this->Mass()) {
            case 500 : return 3.0495761279999996 * fb;
            case 1000 : return 0.22623192864 * fb;
            case 2000 : return 0.005720855039999999 * fb;
            case 3000 : return 0.0003035467008 * fb;
            case 4000 : return 0.000020556093312 * fb;
            default:
//                 ERROR("Signal Crosssection", "unhandled case");
                return fb;
            } ;
        case heavyhiggs::Collider::LE:
            switch (this->Mass()) {
            case 500 : return 247.86995327999998 * fb;
            case 700 : return 109.26120959999999 * fb;
            case 1000 : return 39.81212064 * fb;
            case 1500 : return 10.639675008 * fb;
            case 2000 : return 3.8189750399999998 * fb;
            case 3000 : return 0.7737415487999998 * fb;
            case 4000 : return 0.22421177856 * fb;
            case 5000 : return 0.07985005056 * fb;
            case 6000 : return 0.03297554496 * fb;
            case 8000 : return 0.007364981375999998 * fb;
            case 10000 : return 0.0020553163775999996 * fb;
            case 12000 : return 0.0006632091647999999 * fb;
            case 15000 : return 0.00014951794176 * fb;
            case 20000 : return 0.000016388469792 * fb;
            default:
//                 ERROR("Signal Crosssection", "unhandled case");
                return fb;
            }
        default:
//             ERROR("Signal Crosssection", "unhandled case");
            return fb;
        }
    }

    int PassPreCut(Event const& event, Tag) const {
//         INFO("pass pre cut");
        std::vector<Particle> particles = event.Partons().GenParticles();
        std::vector<Particle> quarks = SortedByPt(CopyIf5Quark(particles));
        quarks = SortedByPt(RemoveIfMother(quarks, Id::top));
        if (quarks.empty()) {
            //       if (Tag == Tag::signal && PreCut() > 0 && !(Tagger == BottomTagger || Tagger == HBottomReader))
            //       if (PreCut() > 0)
//             ERROR("Not enough bottom quarks", Quarks.size());
            return 0;
        } else if (quarks.front().Pt() < this->PreCut()) return 0;
        std::vector<Particle> TopQuarks = SortedByPt(CopyIfParticle(particles, Id::top));
        if (TopQuarks.size() != 2) {
//             ERROR("Not enough top quarks", TopQuarks.size());
            return 0;
        } else if (TopQuarks.front().Pt() < this->PreCut()) return 0;
        if (event.Hadrons().MissingEt().Pt() < this->MissingEt()) return 0;
        std::vector<Lepton> leptons = SortedByPt(event.Leptons().leptons());
        if (leptons.empty()) return 0;
        if (leptons.front().Pt() < this->LeptonPt()) return 0;
        std::vector<Jet> jets = event.Hadrons().Jets();
        if (jets.size() < 4) return 0;
        return 1;
    }
    int BackgroundFileNumber() const {
        switch (this->Collider()) {
        case heavyhiggs::Collider::LHC :
            switch (this->PreCut()) {
            case 0 :
                //                 return 1;
                return 79; // < should be switched on
            case 250 :
                return 58; // < should be switched on
            default :
                return 1;
            }
        case heavyhiggs::Collider::LE :
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
        switch (this->Collider()) {
        case heavyhiggs::Collider::LHC :
            switch (this->PreCut()) {
            case 0 : return 97.54 * 2 * fb;
            case 250 : return 4.206 * 2 * fb;
            }
        case heavyhiggs::Collider::LE: {
            switch (this->PreCut()) {
            case 0 : return 3564. * 2 * fb;
            case 300 : return 187.3 * 2 * fb;
            case 1500 : return 0.447 * 2 * fb;
            case 2500 : return 0.0442 * 2 * fb;
            }
        }
        default :
//             ERROR("unhandled case");
            return fb;
        }
    }

};

}

}
