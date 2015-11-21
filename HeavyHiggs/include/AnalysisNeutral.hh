#pragma once

#include "AnalysisHeavyHiggs.hh"
#include "Vector.hh"
#include "Sort.hh"

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
class AnalysisNeutral : public AnalysisHeavyHiggs<Tagger>
{

public:

    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::Hbb);
            break;
        case Tag::background :
            this->NewFile(tag, Process::tt);
            break;
        }
    }

    std::string AnalysisName() const final {
      //        return  "Neutral-" + ColliderName(collider_type()) + "-" + Name(PreCut()) + "-" + Name(Mass()) + "-Eta2.5";
      return  "Neutral-" + Name(this->collider_type()) + "-" + boca::Name(this->PreCut()) + "-" + boca::Name(this->Mass());
    };

private:

    Crosssection SignalCrosssection() const {
        switch (this->collider_type()) {
        case Collider::LHC:
            switch (this->Mass()) {
            case 500 : return 25.528929726502543 * pb;
            case 1000 : return 1.2783507034600217 * pb;
            case 2000 : return 0.021907574118663196 * pb;
            default :
                Error("Signal Crosssection", "unhandled case");
                return pb;
            } ;
        case Collider::FHC:
        case Collider::LE:
            switch (this->Mass()) {
            case 500 : return 973.5805772514352 * pb;
            case 1000 : return 123.02005671222373 * pb;
            case 1500 : return 28.624904980998327 * pb;
            case 2000 : return 9.485582085140349 * pb;
            case 3000 : return 1.7540841248835577 * pb;
            case 4000 : return 0.4851939478031553 * pb;
            case 5000 : return 0.16696738296715652 * pb;
            case 6000 : return 0.06731697180862359 * pb;
            case 7000 : return 0.029372932414373627 * pb;
            case 8000 : return 0.014255221936825225 * pb;
            case 10000 : return 0.0038428602375120795 * pb;
            case 12000 : return 0.0012219523755405267 * pb;
            case 15000 : return 0.00026507004708327343 * pb;
            case 20000 : return 0.000028218388829563033 * pb;
            default:
                Error("Signal Crosssection", "unhandled case");
                return pb;
            }
        default:
            Error("Signal Crosssection", "unhandled case");
            return pb;
        }
    }

//     std::string ProcessName() const override {
//         return "Neutral";
//     }

    int PassPreCut(Event const& event, Tag) const override {
      std::vector<Particle> Particles = event.Partons().GenParticles();
       std::vector<Particle> Tops = CopyIfParticle(Particles, Id::top);
        if (Tops.size() != 2) return 0;
        else {
            if (Tops.at(0).pt() < this->PreCut() / GeV) return 0;
            if (Tops.at(1).pt() < this->PreCut() / GeV) return 0;
        }
        if (event.Hadrons().MissingEt().pt() < this->MissingEt() / GeV) return 0;
       std::vector<Jet> Leptons = SortedByPt(event.Leptons().leptons());
        if (Leptons.empty()) return 0;
        if (Leptons.front().pt() < this->LeptonPt() / GeV) return 0;
       std::vector<Jet> jets = event.Hadrons().Jets();
        if (jets.size() < 4) return 0;
        return 1;
    }

};

}

}
