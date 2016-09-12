#pragma once

#include "heavyhiggs/analysis/HeavyHiggs.hh"
#include "boca/multiplets/Sort.hh"
#include "boca/multiplets/Particles.hh"

namespace heavyhiggs {

namespace analysis {

/**
 *
 * @brief analysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class Fusion : public HeavyHiggs<Tagger_> {

public:

    void SetFiles(Tag tag, Stage)override {
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

    std::string Name() const final
    {
      return  "Fusion-" + boca::Name(this->Collider()) + "-" + boca::units::Name(this->PreCut()) + "-" + boca::units::Name(this->Mass());
    }

private:

    int BackgroundFileNumber() const override {
        switch (this->Collider()) {
        case Collider::lhc :
            switch (static_cast<int>(this->PreCut() / GeV)) {
            case  0 :
                return 79;
            //                 return 1; // < this must be removed !!
            case  250 :
                return 41;
            }
        case Collider::future :
            switch (static_cast<int>(this->PreCut() / GeV)) {
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
        switch (this->Collider()) {
        case Collider::lhc:
            switch (this->Mass()) {
            case 400 : return 1463.1219866990498 * fb;
            case 500 : return 512.5992335098167 * fb;
            case 1000 : return 10.942712198242141 * fb;
            case 2000 : return 0.10283305582403454 * fb;
            case 3000 : return 0.003583086718061121 * fb;
            case 4000 : return 0.00020344209136808554 * fb;
            default:
//                 ERROR("unhandled case");
                return pb;
            } ;
        case Collider::future:
            switch (this->Mass()) {
            // tan beta = 2
            case 400 : return 48385.16604388162 * fb;
            case 500 : return 21753.261647408788 * fb;
            case 700 : return 5388.806849750459 * fb;
            case 800 : return 2987.6531326979493 * fb;
            case 1000 : return 1062.9847850641604 * fb;
            case 1500 : return 148.78718745483314 * fb;
            case 2000 : return 33.76298845204924 * fb;
            case 3000 : return 3.715444262833449 * fb;
            case 4000 : return 0.7052693313851425 * fb;
            case 5000 : return 0.1841745400744028 * fb;
            case 6000 : return 0.058156868371520024 * fb;
            case 8000 : return 0.008651760976852958 * fb;
            case 10000 : return 0.0018198636858628185 * fb;
            case 12000 : return 0.0004674423191995998 * fb;
            case 15000 : return 0.000046 * fb; //<this is just wrong get the right numbers
            case 20000 : return 0.0000046 * fb; //<this is just wrong get the right numbers
            default:
//                 ERROR("unhandled case");
                return pb;
            }
        default:
//             ERROR("unhandled case");
            return pb;
        }
    }

    int PassPreCut(boca::Event const& event, Tag) const final
    {
       auto particles = event.GenParticles();
        particles = CopyIfParticle(particles, Id::top);
        if (particles.size() != 2) {
//             ERROR("Not enough top quarks", Particles.size());
            return 0;
        } else {
          if (particles.at(0).Pt() < this->PreCut()) return 0;
          if (particles.at(1).Pt() < this->PreCut()) return 0;
        }
        if (event.MissingEt().Pt() < this->MissingEt()) return 0;
       auto leptons = SortedByPt(event.Leptons());
       if (leptons.empty()) return 0;
       if (leptons.front().Pt() < this->LeptonPt()) return 0;
       auto jets = event.Jets();
        if (jets.size() < 4) return 0;
        return 1;
    }

};

}

}
