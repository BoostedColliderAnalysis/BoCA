#pragma once

#include "AnalysisHeavyHiggs.hh"

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
        this->tagger().SetAnalysisName(ProjectName());
//  this->pre_cuts().SetPtLowerCut(Id::top,100);
    }

    void SetFiles(Tag tag) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, SignalCrosssection(Process::Htt), Process::Htt);
            this->NewFile(tag, SignalCrosssection(Process::Htwb), Process::Htwb);
            break;
        case Tag::background :
            if (this->tagger().Name() == "JetPair") this->NewFile(tag, SignalCrosssection(Process::Htt), Process::Htt);
            if (this->tagger().Name() == "JetPair") this->NewFile(tag, SignalCrosssection(Process::Htwb), Process::Htwb);
            this->NewFile(tag, BackgroundCrosssection(Process::ttwwbb), Process::ttwwbb);
            this->NewFile(tag, BackgroundCrosssection(Process::ttwbb), Process::ttwbb);
            break;
        }
    }

    std::string ProjectName() const final {
        //        return  ProcessName() + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV-Eta2.5";
        return  ProcessName() + "-" + Name(this->collider_type()) + "-" + std::to_string(this->Mass()) + "GeV";
    };

    Crosssection SignalCrosssection(Process process) const {
        Crosssection crosssection(1.*femto * barn);
        switch (this->collider_type()) {
        case Collider::LHC:
            switch (process) {
            case Process::Htt:
                switch (this->Mass()) {
                case 500:
                    return crosssection * 0.911648;
                case 700:
                    return crosssection * 0.346647;
                case 800:
                    return crosssection * 0.225386;
                case 1000:
                    return crosssection * 0.10028;
                case 1500:
                    return crosssection * 0.0168305;
                case 2000:
                    return crosssection * 0.00345315;
                default:
                    Error("unhandled case");
                    return crosssection;
                }
            case Process::Htwb:
                switch (this->Mass()) {
                case 500:
                    return crosssection;
                case 700:
                    return crosssection;
                case 800:
                    return crosssection;
                case 1000:
                    return crosssection;
                case 1500:
                    return crosssection;
                case 2000:
                    return crosssection;
                default:
                    Error("unhandled case");
                    return crosssection;
                }
            default:
                Error("unhandled case");
                return crosssection;
            };
        case Collider::FHC:
        case Collider::LE:
            switch (process) {
            case Process::Htt:
                switch (this->Mass()) {
                case 500:
                    return crosssection * 152.154;
                case 700:
                    return crosssection * 79.3982;
                case 800:
                    return crosssection * 60.9656;
                case 1000:
                    return crosssection * 36.5579;
                case 1500:
                    return crosssection * 12.4039;
                case 2000:
                    return crosssection * 5.09533;
                case 3000:
                    return crosssection * 1.21763;
                case 4000:
                    return crosssection * 0.385975;
                case 5000:
                    return crosssection * 0.14659;
                case 6000:
                    return crosssection * 0.062513;
                case 7000:
                    return crosssection * 0.026579;
                case 8000:
                    return crosssection * 0.0132781;
                case 10000:
                    return crosssection * 0.00380676;
                default:
                    Error("unhandled case");
                    return crosssection;
                }
            case Process::Htwb:
                switch (this->Mass()) {
                case 500:
                    return crosssection * 117.041;
                case 700:
                    return crosssection * 79.5743;
                case 800:
                    return crosssection * 66.4861;
                case 1000:
                    return crosssection * 47.8374;
                case 1500:
                    return crosssection * 23.1449;
                case 2000:
                    return crosssection * 12.5153;
                case 3000:
                    return crosssection * 4.60995;
                case 4000:
                    return crosssection * 2.01434;
                case 5000:
                    return crosssection * 0.975944;
                case 6000:
                    return crosssection * 0.509747;
                case 7000:
                    return crosssection * 0.256938;
                case 8000:
                    return crosssection * 0.148312;
                case 10000:
                    return crosssection * 0.0539546;
                default:
                    Error("unhandled case");
                    return crosssection;
                }
            default:
                Error("unhandled case");
                return crosssection;
            }
        default:
            Error("unhandled case");
            return crosssection;
        }
    }

    Crosssection BackgroundCrosssection(Process process) const {
      Crosssection crosssection(1.*femto * barn);
        switch (this->collider_type()) {
        case Collider::LHC :
            switch (process) {
            case Process::ttwwbb:
              return crosssection;
            case Process::ttwbb:
              return crosssection;
            default:
                Error("unhandled case");
                return crosssection;
            }
        case Collider::LE:
            switch (process) {
            case Process::ttwwbb:
              return crosssection * 396.;
            case Process::ttwbb:
              return crosssection * 1.3204;
            default:
                Error("unhandled case");
                return crosssection;
            }
        default:
            Error("unhandled case");
            return crosssection;
        }
    }


private:

    std::string ProcessName() const override {
        return "NeutralFourTop";
    }

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

        if (event.Hadrons().MissingEt().pt() < this->MissingEt()) return 0;
        Jets Leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
        if (Leptons.size() < 2) return 0;
//      if (Leptons.at(0).pt() < this->LeptonPt()) return 0;
//  if (Leptons.at(1).pt() < this->LeptonPt()) return 0;
        int positive_lepton = 0;
        int negative_lepton = 0;
        for (auto const & lepton : Leptons) {
            if (lepton.pt() > this->LeptonPt() && lepton.user_info<JetInfo>().Charge() > 0)positive_lepton++;
            if (lepton.pt() > this->LeptonPt() && lepton.user_info<JetInfo>().Charge() < 0)negative_lepton++;
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
