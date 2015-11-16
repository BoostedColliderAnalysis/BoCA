#pragma once

#include "AnalysisHeavyHiggs.hh"

#include "JetPairTagger.hh"
#include "Doublet.hh"
#include "Debug.hh"

namespace boca
{

namespace heavyhiggs
{

template<typename Tagger>
class AnalysisNeutralFourTop : public AnalysisHeavyHiggs<Tagger>
{

public:

    AnalysisNeutralFourTop() {
//  this->pre_cuts().PtLowerCut().Set(Id::top,100);
    }

    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, SignalCrosssection(Process::Htt), Process::Htt);
            this->NewFile(tag, SignalCrosssection(Process::Htwb), Process::Htwb);
            break;
        case Tag::background :
          if (this->template TaggerIs<JetPairTagger>()) this->NewFile(tag, SignalCrosssection(Process::Htt), Process::Htt);
          if (this->template TaggerIs<JetPairTagger>()) this->NewFile(tag, SignalCrosssection(Process::Htwb), Process::Htwb);
            this->NewFile(tag, BackgroundCrosssection(Process::ttwwbb), Process::ttwwbb);
            this->NewFile(tag, BackgroundCrosssection(Process::ttwbb), Process::ttwbb);
            break;
        }
    }

    std::string AnalysisName() const final {
      //        return  "NeutralFourTop-" + ColliderName(collider_type()) + "-" + Name(PreCut()) + "-" + Name(Mass()) + "-Eta2.5";
      return  "NeutralFourTop-" + Name(this->collider_type()) + "-" + boca::Name(this->Mass());
    };

    Crosssection SignalCrosssection(Process process) const {
        switch (this->collider_type()) {
        case Collider::LHC:
            switch (process) {
            case Process::Htt:
                switch (Int(this->Mass())) {
                case 500 : return 0.911648 * pb;
                case 700 : return 0.346647 * pb;
                case 800 : return 0.225386 * pb;
                case 1000 : return 0.10028 * pb;
                case 1500 : return 0.0168305 * pb;
                case 2000 : return 0.00345315 * pb;
                default:
                    Error("unhandled case");
                    return pb;
                }
            case Process::Htwb:
                switch (Int(this->Mass())) {
                case 500 : return pb;
                case 700 : return pb;
                case 800 : return pb;
                case 1000 : return pb;
                case 1500 : return pb;
                case 2000 : return pb;
                default:
                    Error("unhandled case");
                    return pb;
                }
            default:
                Error("unhandled case");
                return pb;
            };
        case Collider::FHC:
        case Collider::LE:
            switch (process) {
            case Process::Htt:
                switch (Int(this->Mass())) {
                case 500 : return 152.154 * pb;
                case 700 : return 79.3982 * pb;
                case 800 : return 60.9656 * pb;
                case 1000 : return 36.5579 * pb;
                case 1500 : return 12.4039 * pb;
                case 2000 : return 5.09533 * pb;
                case 3000 : return 1.21763 * pb;
                case 4000 : return 0.385975 * pb;
                case 5000 : return 0.14659 * pb;
                case 6000 : return 0.062513 * pb;
                case 7000 : return 0.026579 * pb;
                case 8000 : return 0.0132781 * pb;
                case 10000 : return 0.00380676 * pb;
                default:
                    Error("unhandled case");
                    return pb;
                }
            case Process::Htwb:
                switch (Int(this->Mass())) {
                case 500 : return 117.041 * pb;
                case 700 : return 79.5743 * pb;
                case 800 : return 66.4861 * pb;
                case 1000 : return 47.8374 * pb;
                case 1500 : return 23.1449 * pb;
                case 2000 : return 12.5153 * pb;
                case 3000 : return 4.60995 * pb;
                case 4000 : return 2.01434 * pb;
                case 5000 : return 0.975944 * pb;
                case 6000 : return 0.509747 * pb;
                case 7000 : return 0.256938 * pb;
                case 8000 : return 0.148312 * pb;
                case 10000 : return 0.0539546 * pb;
                default:
                    Error("unhandled case");
                    return pb;
                }
            default:
                Error("unhandled case");
                return pb;
            }
        default:
            Error("unhandled case");
            return pb;
        }
    }

    Crosssection BackgroundCrosssection(Process process) const {
        switch (this->collider_type()) {
        case Collider::LHC :
            switch (process) {
            case Process::ttwwbb : return pb;
            case Process::ttwbb : return pb;
            default:
                Error("unhandled case");
                return pb;
            }
        case Collider::LE:
            switch (process) {
            case Process::ttwwbb : return 396. * pb;
            case Process::ttwbb : return 1.3204 * pb;
            default:
                Error("unhandled case");
                return pb;
            }
        default:
            Error("unhandled case");
            return pb;
        }
    }


private:

//     std::string ProcessName() const override {
//         return "NeutralFourTop";
//     }

    int PassPreCut(Event const& event, Tag) const override {
        Jets Particles = event.Partons().GenParticles();

        Jets Tops = CopyIfParticle(Particles, Id::top);
        Jets Bottoms = CopyIfParticle(Particles, Id::bottom);
//         if(Bottoms.size() < 4) return 0;
//
//         if (Bottoms.at(0).pt() < this->BottomPt()) return 0;
//         if (Bottoms.at(1).pt() < this->BottomPt()) return 0;
//         if (Bottoms.at(2).pt() < this->BottomPt()) return 0;
//         if (Bottoms.at(3).pt() < this->BottomPt()) return 0;

        if (event.Hadrons().MissingEt().pt() < this->MissingEt() / GeV) return 0;
        Jets Leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
        if (Leptons.size() < 2) return 0;
//      if (Leptons.at(0).pt() < this->LeptonPt()) return 0;
//  if (Leptons.at(1).pt() < this->LeptonPt()) return 0;
        int positive_lepton = 0;
        int negative_lepton = 0;
        for (auto const & lepton : Leptons) {
            if (lepton.pt() > this->LeptonPt() / GeV && lepton.user_info<JetInfo>().Charge() > 0)positive_lepton++;
            if (lepton.pt() > this->LeptonPt() / GeV && lepton.user_info<JetInfo>().Charge() < 0)negative_lepton++;
        }

        if (positive_lepton < 2 && negative_lepton < 2) return 0;
        if ((positive_lepton + negative_lepton) > 2) return 0;

        Jets jets = event.Hadrons().Jets();
        if (jets.size() < 4)
            return 0;
        return 1;
    }

};

}

}
