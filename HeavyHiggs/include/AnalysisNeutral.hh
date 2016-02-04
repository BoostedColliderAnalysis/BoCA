#pragma once

#include "AnalysisHeavyHiggs.hh"
#include "Sort.hh"
#include "Debug.hh"

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
        //        return  "Neutral-" + ColliderName(Collider()) + "-" + Name(PreCut()) + "-" + Name(Mass()) + "-Eta2.5";
        return  "Neutral-" + Name(this->Collider()) + "-" + boca::Name(this->PreCut()) + "-" + boca::Name(this->Mass());
    };

private:

    Crosssection SignalCrosssection() const {
        switch (this->Collider()) {
        case Collider::LHC:
            switch (this->Mass()) {
            case 500 : return 25.528929726502543 * fb;
            case 1000 : return 1.2783507034600217 * fb;
            case 2000 : return 0.021907574118663196 * fb;
                DEFAULT(to_int(this->Mass()), fb);
            }
        case Collider::FHC:
        case Collider::LE:
            switch (this->Mass()) {
            case 500 : return 973.5805772514352 * fb;
            case 1000 : return 123.02005671222373 * fb;
            case 1500 : return 28.624904980998327 * fb;
            case 2000 : return 9.485582085140349 * fb;
            case 3000 : return 1.7540841248835577 * fb;
            case 4000 : return 0.4851939478031553 * fb;
            case 5000 : return 0.16696738296715652 * fb;
            case 6000 : return 0.06731697180862359 * fb;
            case 7000 : return 0.029372932414373627 * fb;
            case 8000 : return 0.014255221936825225 * fb;
            case 10000 : return 0.0038428602375120795 * fb;
            case 12000 : return 0.0012219523755405267 * fb;
            case 15000 : return 0.00026507004708327343 * fb;
            case 20000 : return 0.000028218388829563033 * fb;
                DEFAULT(to_int(this->Mass()), fb);
            }
            DEFAULT(to_int(this->Collider()), fb);
        }
    }

//     std::string ProcessName() const override {
//         return "Neutral";
//     }

    int PassPreCut(Event const& event, Tag) const override {
        std::vector<Particle> particles = event.Partons().GenParticles();
        std::vector<Particle> tops = CopyIfParticle(particles, Id::top);
        if (tops.size() != 2) return 0;
        else {
            if (tops.at(0).Pt() < this->PreCut()) return 0;
            if (tops.at(1).Pt() < this->PreCut()) return 0;
        }
        if (event.Hadrons().MissingEt().Pt() < this->MissingEt()) return 0;
        std::vector<Lepton> leptons = SortedByPt(event.Leptons().leptons());
        if (leptons.empty()) return 0;
        if (leptons.front().Pt() < this->LeptonPt()) return 0;
        std::vector<Jet> jets = event.Hadrons().Jets();
        if (jets.size() < 4) return 0;
        return 1;
    }

};

}

}
