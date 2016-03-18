#pragma once

#include "AnalysisHeavyHiggs.hh"

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
        switch (tag) {
        case Tag::signal : this->NewFile(tag, Process::Hbb);
            break;
        case Tag::background : this->NewFile(tag, Process::tt);
            break;
        }
    }

    std::string AnalysisName() const override {
        //        return  "Neutral-" + ColliderName(Collider()) + "-" + Name(PreCut()) + "-" + Name(Mass()) + "-Eta2.5";
        return  "Neutral-" + Name(this->Collider()) + "-" + boca::Name(this->PreCut()) + "-" + boca::Name(this->Mass()) + "3-jet-cut-large";
    };

private:

    int PassPreCut(Event const& event, Tag tag) const override {
//         if (tag == Tag::background) return 1;
//         std::vector<Particle> particles = event.Partons().GenParticles();
//         for (auto const & particle : particles) ERROR(boca::Name(particle.Info().Family().Member(Relative::particle).Id()), boca::Name(particle.Info().Family().Member(Relative::mother).Id()), boca::Name(particle.Info().Family().Member(Relative::step_mother).Id()), boca::Name(particle.Info().Family().Member(Relative::grand_mother).Id()));
//         std::vector<Particle> bottoms = SortedByPt(CopyIfParticle(particles, Id::bottom));
//         std::vector<Particle> tags;
//         for (auto const & bottom : bottoms) if (bottom.Info().Family().Member(Relative::mother).Id() != to_int(Id::heavy_higgs) && bottom.Info().Family().Member(Relative::mother).Id() != to_int(Id::higgs) && abs(bottom.Info().Family().Member(Relative::mother).Id()) != to_int(Id::top) && bottom.Pt() > 20_GeV && abs(bottom.Rap()) < 2.5_rad) tags.emplace_back(bottom);

//         if (tags.size() < 2) return 0;

//         static int sum = 0;
//         static int zero = 0;
//         static int one = 0;
//         static int two = 0;
//
//         ++sum;
//         switch (tags.size()) {
//         case 0 : ++zero; break;
//         case 1 : ++one; break;
//         case 2 : ++two; break;
//         default : ERROR(tags.size());
//         }
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
