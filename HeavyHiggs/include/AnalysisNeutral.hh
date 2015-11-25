#pragma once

#include "AnalysisHeavyHiggs.hh"
#include "Vector.hh"
// #include "Debug.hh"

namespace analysis {

/**
 * @brief Namespace for the heavy higgs analyses
 *
 */

namespace heavyhiggs {

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisNeutral : public AnalysisHeavyHiggs<Tagger> {

public:

    AnalysisNeutral()
    {
//       Info(ProjectName());
      this->tagger().SetAnalysisName(ProjectName());
    }

    void SetFiles(Tag tag) final {
//       Info();
        switch (tag)
        {
        case Tag::signal :
            this->NewFile(tag, SignalCrosssection(), Process::Hbb);
            break;
        case Tag::background :
//             if (this->tagger().Name() == "JetPair") this->NewFile(tag, SignalCrosssection(), Process::Hbb);
            this->NewFile(tag, BackgroundCrosssection(), Process::tt);
            break;
        }
    }

    std::string ProjectName() const final
    {
//       Info();
      return  ProcessName() + "-" + Name(this->collider_type()) + "-" + std::to_string(this->PreCut()) + "GeV-" + std::to_string(this->Mass()) + "GeV_Isolated";
    };

private:

    float SignalCrosssection() const
    {
//       Info();
        switch (this->collider_type()) {
        case Collider::LHC:
            switch (this->Mass()) {
            case 500:
                return 25.528929726502543;
            case 1000:
                return 1.2783507034600217;
            case 2000:
                return 0.021907574118663196;
            default:
                Error("Signal Crosssection", "unhandled case");
                return 1;
            } ;
        case Collider::FHC:
        case Collider::LE:
            switch (this->Mass()) {
            case 500:
                return 973.5805772514352;
            case 1000:
                return 123.02005671222373;
            case 1500:
                return 28.624904980998327;
            case 2000:
                return 9.485582085140349;
            case 3000:
                return 1.7540841248835577;
            case 4000:
                return 0.4851939478031553;
            case 5000:
                return 0.16696738296715652;
            case 6000:
                return 0.06731697180862359;
            case 7000:
                return 0.029372932414373627;
            case 8000:
                return 0.014255221936825225;
            case 10000:
                return 0.0038428602375120795;
            case 12000:
                return 0.0012219523755405267;
            case 15000:
                return 0.00026507004708327343;
            case 20000:
                return 0.000028218388829563033;
            default:
                Error("Signal Crosssection", "unhandled case");
                return 1;
            }
        default:
            Error("Signal Crosssection", "unhandled case");
            return 1;
        }
    }
    
    float BackgroundCrosssection() const
    {
//       Info();
      switch (this->collider_type()) {
        case Collider::LHC:
          switch (this->PreCut()) {
            case 0:
              return 97.54*2*1000;
            case 250:
              return 5.698*2*1000;
            default:
              Error("BackgroundCrosssection", "unhandled case");
              return 1;
          } ;
            case Collider::FHC:
            case Collider::LE:
              switch (this->PreCut()) {
                case 0:
                  return 7130000;
                case 300:
                  return 356000;
                case 1500:
                  return 505;
                case 2500:
                  return 44.4;
                default:
                  Error("BackgroundCrosssection", "unhandled case");
                  return 1;
              }
                default:
                  Error("BackgroundCrosssection", "unhandled case");
                  return 1;
      }
    }

    std::string ProcessName() const override
    {
//       Info();
        return "Neutral";
    }

    int PassPreCut(const Event& event, Tag) const override
    {
//       Info();
        Jets Particles = event.Partons().GenParticles();
        Jets Tops = CopyIfParticle(Particles, Id::top);
        if (Tops.size() != 2) return 0;        
        if (Tops.at(0).pt() < this->PreCut()) return 0;
        if (Tops.at(1).pt() < this->PreCut()) return 0;      
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
