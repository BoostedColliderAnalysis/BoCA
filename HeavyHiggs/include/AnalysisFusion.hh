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
class AnalysisFusion : public AnalysisHeavyHiggs<Tagger>
{

public:

    AnalysisFusion() {
        this->tagger().set_analysis_name(ProjectName());
    }

    void SetFiles(const Tag tag) {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::H0);
            break;
        case Tag::background :
            this->NewFile(tag, Process::tt);
            break;
        }
    }

    std::string ProcessName() const {
        return "Fusion";
    }

    std::string ProjectName() const {
      return  ProcessName() + "-" + Name(this->collider_type()) + "-" + std::to_string(this->PreCut()) + "GeV-" + std::to_string(this->Mass()) + "GeV";
    }

private:

    int BackgroundFileNumber() const {
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

    float SignalCrosssection() const {
      switch (this->collider_type()) {
        case Collider::LHC:
          switch (this->Mass()) {
            case 400 :
                return 1463.1219866990498;
            case 500:
                return 512.5992335098167;
            case 1000:
                return 10.942712198242141;
            case 2000:
                return 0.10283305582403454;
            case 3000:
                return 0.003583086718061121;
            case 4000:
                return 0.00020344209136808554;
            default:
//                 Error("unhandled case");
                return 1;
            } ;
        case Collider::LE:
          switch (this->Mass()) {
                // tan beta = 2
            case 400 :
                return 48385.16604388162;
            case 500 :
                return 21753.261647408788;
            case 700 :
                return 5388.806849750459;
            case 800:
                return 2987.6531326979493;
            case 1000:
                return 1062.9847850641604;
            case 1500:
                return 148.78718745483314;
            case 2000:
                return 33.76298845204924;
            case 3000:
                return 3.715444262833449;
            case 4000:
                return 0.7052693313851425;
            case 5000:
                return 0.1841745400744028;
            case 6000:
                return 0.058156868371520024;
            case 8000:
                return 0.008651760976852958;
            case 10000:
                return 0.0018198636858628185;
            case 12000:
                return 0.0004674423191995998;
            case 15000:
                return 0.000046; //<this is just wrong get the right numbers
            case 20000:
                return 0.0000046; //<this is just wrong get the right numbers
            default:
//                 Error("unhandled case");
                return 1;
            }
        default:
//             Error("unhandled case");
            return 1;
        }
    }

    int PassPreCut(const Event &event) {
        Jets Particles = event.Partons().GenParticles();
        Particles = RemoveIfWrongAbsParticle(Particles, Id::top);
        if (Particles.size() != 2) {
//             Error("Not enough top quarks", Particles.size());
            return 0;
        } else {
            if (Particles.at(0).pt() < this->PreCut()) return 0;
            if (Particles.at(1).pt() < this->PreCut()) return 0;
        }

        if (event.Hadrons().MissingEt().pt() < this->MissingEt()) return 0;
        Jets Leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
        if (Leptons.empty()) return 0;
        if (Leptons.front().pt() < this->LeptonPt()) return 0;
        Jets jets = event.Hadrons().Jets();
        if (jets.size() < 4) return 0;
        return 1;
    }

};

}

}
