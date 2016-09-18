#pragma once

#include "heavyhiggs/analysis/HeavyHiggs.hh"
#include "boca/multiplets/Sort.hh"
#include "boca/multiplets/Particles.hh"

namespace heavyhiggs
{

namespace analysis
{

/**
 *
 * @brief analysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class Charged : public HeavyHiggs<Tagger_>
{

public:

    void SetFiles(Phase const& phase) override {
        switch (phase.Tag()) {
        case Tag::signal :
            this->AddSignal(Process::Htb);
            break;
        case Tag::background :
            this->AddBackground(Process::tt);
            break;
        }
    }

    std::string Name() const override {
        return  "Charged-" + boca::Name(this->Collider()) + "-" + boca::units::Name(this->PreCut()) + "-" + boca::units::Name(this->Mass());
    }

private:

    Crosssection SignalCrosssection() const {
        switch (this->Collider()) {
        case boca::Collider::lhc:
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
        case boca::Collider::future:
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

    bool PassPreCut(boca::Event const& event) const override {
//         INFO("pass pre cut");
        auto particles = event.GenParticles();
        auto quarks = SortedByPt(CopyIf5Quark(particles));
        quarks = SortedByPt(RemoveIfMother(quarks, Id::top));
        if (quarks.empty()) {
            //       if (Tag == Tag::signal && PreCut() > 0 && !(Tagger == tagger::Bottom || Tagger == HBottomReader))
            //       if (PreCut() > 0)
//             ERROR("Not enough bottom quarks", Quarks.size());
            return false;
        } else if (quarks.front().Pt() < this->PreCut()) return false;
        auto TopQuarks = SortedByPt(CopyIfParticle(particles, Id::top));
        if (TopQuarks.size() != 2) {
//             ERROR("Not enough top quarks", TopQuarks.size());
            return false;
        } else if (TopQuarks.front().Pt() < this->PreCut()) return false;
        if (event.MissingEt().Pt() < this->MissingEt()) return false;
        auto leptons = SortedByPt(event.Leptons());
        if (leptons.empty()) return false;
        if (leptons.front().Pt() < this->LeptonPt()) return false;
        auto jets = event.Jets();
        if (jets.size() < 4) return false;
        return true;
    }

    int BackgroundFileNumber() const override {
        switch (this->Collider()) {
        case boca::Collider::lhc :
            switch (static_cast<int>(this->PreCut() / GeV)) {
            case 0 :
                //                 return 1;
                return 79; // < should be switched on
            case 250 :
                return 58; // < should be switched on
            default :
                return 1;
            }
        case boca::Collider::future :
            switch (static_cast<int>(this->PreCut() / GeV)) {
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
        case boca::Collider::lhc :
            switch (this->PreCut()) {
            case 0 : return 97.54 * 2 * fb;
            case 250 : return 4.206 * 2 * fb;
            }
        case boca::Collider::future: {
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
