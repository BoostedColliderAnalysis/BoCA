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

    void SetFiles(Tag tag, Stage)override {
        ERROR0;
        switch (tag) {
        case Tag::signal : this->NewFile(tag, Process::hbb);
            break;
        case Tag::background : this->NewFile(tag, Process::hbb);
            break;
        }
    }

    std::string AnalysisName() const override {
        ERROR0;
        //        return  "Neutral-" + ColliderName(Collider()) + "-" + Name(PreCut()) + "-" + Name(Mass()) + "-Eta2.5";
        return  "Neutral-" + Name(this->Collider()) + "-" + boca::Name(this->PreCut()) + "-" + boca::Name(this->Mass()) + "-Cut";
    };

private:

    Crosssection SignalCrosssection() const {
        ERROR0;
        switch (this->Collider()) {
        case heavyhiggs::Collider::LHC:
            switch (this->Mass()) {
            case 500 : return 25.52 * fb;
            case 1000 : return 1.278 * fb;
            case 2000 : return 0.02190 * fb;
                DEFAULT(to_int(this->Mass()), fb);
            }
        case heavyhiggs::Collider::FHC:
        case heavyhiggs::Collider::LE:
            switch (this->Mass()) {
            case 500 : return 973.5 * fb;
            case 1000 : return 123.0 * fb;
            case 1500 : return 28.62 * fb;
            case 2000 : return 9.485 * fb;
            case 3000 : return 1.754 * fb;
            case 4000 : return 0.4851 * fb;
            case 5000 : return 0.1669 * fb;
            case 6000 : return 0.06731 * fb;
            case 7000 : return 0.02937 * fb;
            case 8000 : return 0.01425 * fb;
            case 10000 : return 0.003842 * fb;
            case 12000 : return 0.001221 * fb;
            case 15000 : return 0.0002650 * fb;
            case 20000 : return 0.00002821 * fb;
                DEFAULT(to_int(this->Mass()), fb);
            }
            DEFAULT(to_int(this->Collider()), fb);
        }
    }

//     std::string ProcessName() const override {
//         return "Neutral";
//     }

    int PassPreCut(Event const& event, Tag) const override {
        ERROR0;
//         std::vector<Particle> particles = event.Partons().GenParticles();
//         std::vector<Particle> bottoms = CopyIfParticle(particles, Id::bottom);
//         std::vector<Particle> tags;
//         for (auto const & bottom : bottoms) if (bottom.Info().Family().Mother().Id() != to_int(Id::heavy_higgs) && bottom.Info().Family().Mother().Id() != to_int(Id::higgs) && abs(bottom.Info().Family().Mother().Id()) != to_int(Id::top) && bottom.Pt() > 10_GeV && abs(bottom.Rap()) < 2.5_rad) tags.emplace_back(bottom);
//         ERROR(tags.size());
//         for (auto const & tag : tags) ERROR(boca::Name(tag.Info().Family().Mother().Id()));
//
//         static int sum = 0;
//         static int zero = 0;
//         static int one = 0;
//         static int two = 0;
//
//         ++sum;
//         if (tags.size() == 0) ++zero;
//         if (tags.size() == 1) ++one;
//
//         if (tags.size() < 2) return 0;
//         two++;
//
//         std::cout << "sum: " << sum << " ; 0: " << zero << " ; 1: " << one << " ; 2: " << two << std::endl;

//         std::vector<Particle> tops = CopyIfParticle(particles, Id::top);
//         if (tops.size() != 2) return 0;
//         else {
//             if (tops.at(0).Pt() < this->PreCut()) return 0;
//             if (tops.at(1).Pt() < this->PreCut()) return 0;
//         }
//         if (event.Hadrons().MissingEt().Pt() < this->MissingEt()) return 0;
//         std::vector<Lepton> leptons = SortedByPt(event.Leptons().leptons());
//         if (leptons.empty()) return 0;
//         if (leptons.front().Pt() < this->LeptonPt()) return 0;
//         std::vector<Jet> jets = event.Hadrons().Jets();
//         if (jets.size() < 4) return 0;
        return 1;
    }

};

}

}
