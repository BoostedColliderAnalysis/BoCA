#pragma once

#include "AnalysisHeavyHiggs.hh"

namespace boca {

namespace heavyhiggs {

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisFusion : public AnalysisHeavyHiggs<Tagger> {

public:

    AnalysisFusion()
    {
        this->tagger().SetAnalysisName(ProjectName());
    }

    void SetFiles(Tag tag) final {
        switch (tag)
        {
        case Tag::signal :
            this->NewFile(tag, Process::H0);
            break;
        case Tag::background :
            this->NewFile(tag, Process::tt);
            break;
        }
    }

//     std::string ProcessName() const override
//     {
//         return "Fusion";
//     }

    std::string ProjectName() const final
    {
      return  "Fusion-" + Name(this->collider_type()) + "-" + boca::Name(this->PreCut()) + "-" + boca::Name(this->Mass()) + "";
    }

private:

    int BackgroundFileNumber() const
    {
        switch (this->collider_type()) {
        case Collider::LHC :
            switch (this->PreCut()) {
            case  0 :
                return 79;
            //                 return 1; // < this must be removed !!
            case  250 :
                return 41;
            }
        case Collider::LE :
            switch (this->PreCut()) {
            case  0 :
                //                   return 98;
                return 1; // < this must be removed !!
            case  100 :
                return 15;
            case  250 :
                return 15;
            case  300 :
                //                   return 110;
                return 1; // < this must be removed !!
            case  1000 :
                return 32;
            case  1500 :
                //                   return 34;
                return 1; // < this must be removed !!
            case  2000 :
                return 26;
            case  2500 :
                //                   return 11;
                return 1; // < this must be removed !!
            }
        default :
            return 1;
        }
    };

    Crosssection SignalCrosssection() const
    {
        switch (this->collider_type()) {
        case Collider::LHC:
            switch (this->Mass()) {
            case 400 : return 1463.1219866990498 * pb;
            case 500 : return 512.5992335098167 * pb;
            case 1000 : return 10.942712198242141 * pb;
            case 2000 : return 0.10283305582403454 * pb;
            case 3000 : return 0.003583086718061121 * pb;
            case 4000 : return 0.00020344209136808554 * pb;
            default:
//                 Error("unhandled case");
                return pb;
            } ;
        case Collider::LE:
            switch (this->Mass()) {
            // tan beta = 2
            case 400 : return 48385.16604388162 * pb;
            case 500 : return 21753.261647408788 * pb;
            case 700 : return 5388.806849750459 * pb;
            case 800 : return 2987.6531326979493 * pb;
            case 1000 : return 1062.9847850641604 * pb;
            case 1500 : return 148.78718745483314 * pb;
            case 2000 : return 33.76298845204924 * pb;
            case 3000 : return 3.715444262833449 * pb;
            case 4000 : return 0.7052693313851425 * pb;
            case 5000 : return 0.1841745400744028 * pb;
            case 6000 : return 0.058156868371520024 * pb;
            case 8000 : return 0.008651760976852958 * pb;
            case 10000 : return 0.0018198636858628185 * pb;
            case 12000 : return 0.0004674423191995998 * pb;
            case 15000 : return 0.000046 * pb; //<this is just wrong get the right numbers
            case 20000 : return 0.0000046 * pb; //<this is just wrong get the right numbers
            default:
//                 Error("unhandled case");
                return pb;
            }
        default:
//             Error("unhandled case");
            return pb;
        }
    }

    int PassPreCut(Event const& event, Tag) const final
    {
        Jets Particles = event.Partons().GenParticles();
        Particles = CopyIfParticle(Particles, Id::top);
        if (Particles.size() != 2) {
//             Error("Not enough top quarks", Particles.size());
            return 0;
        } else {
          if (Particles.at(0).pt() < to_float(this->PreCut())) return 0;
          if (Particles.at(1).pt() < to_float(this->PreCut())) return 0;
        }
        if (event.Hadrons().MissingEt().pt() < to_float(this->MissingEt())) return 0;
        Jets Leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
        if (Leptons.empty()) return 0;
        if (Leptons.front().pt() < to_float(this->LeptonPt())) return 0;
        Jets jets = event.Hadrons().Jets();
        if (jets.size() < 4)
            return 0;
        return 1;
    }

};

}

}
