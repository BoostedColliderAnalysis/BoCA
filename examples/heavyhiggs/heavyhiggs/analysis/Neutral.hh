#pragma once

#include "heavyhiggs/analysis/HeavyHiggs.hh"

namespace heavyhiggs
{

namespace analysis
{

/**
 *
 * @brief analysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class Neutral : public HeavyHiggs<Tagger_>
{

public:

    void SetFiles(Phase const& phase) override {
        switch (phase.Tag()) {
        case Tag::signal :
            this->AddSignal(Process::Hbb);
            break;
        case Tag::background :
            this->AddBackground(Process::tt);
            break;
        }
    }

    std::string Name() const override {
        //        return  "Neutral-" + ColliderName(Collider()) + "-" + Name(PreCut()) + "-" + Name(Mass()) + "-Eta2.5";
        return  "Neutral-" + boca::Name(this->Collider()) + "-" + boca::units::Name(this->PreCut()) + "-" + boca::units::Name(this->Mass()) + "3-jet-bdt-large2";
    };

private:

    bool PassPreCut(boca::Event const&) const override {
//         if (tag == Tag::background) return true;
//         std::vector<Particle> particles = event.GenParticles();
//         for (auto const & particle : particles) ERROR(boca::Name(particle.Info().Family().Member(Relative::particle).Id()), boca::Name(particle.Info().Family().Member(Relative::mother).Id()), boca::Name(particle.Info().Family().Member(Relative::step_mother).Id()), boca::Name(particle.Info().Family().Member(Relative::grand_mother).Id()));
//         std::vector<Particle> bottoms = SortedByPt(CopyIfParticle(particles, Id::bottom));
//         std::vector<Particle> tags;
//         for (auto const & bottom : bottoms) if (bottom.Info().Family().Member(Relative::mother).Id() != to_int(Id::heavy_higgs) && bottom.Info().Family().Member(Relative::mother).Id() != to_int(Id::higgs) && abs(bottom.Info().Family().Member(Relative::mother).Id()) != to_int(Id::top) && bottom.Pt() > 20_GeV && abs(bottom.Rap()) < 2.5_rad) tags.emplace_back(bottom);

//         if (tags.size() < 2) return false;

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
//         if (tops.size() != 2) return false;
//         else {
//             if (tops.at(0).Pt() < this->PreCut()) return false;
//             if (tops.at(1).Pt() < this->PreCut()) return false;
//         }
//         if (event.MissingEt().Pt() < this->MissingEt()) return false;
//         std::vector<Lepton> leptons = SortedByPt(event.Leptons());
//         if (leptons.empty()) return false;
//         if (leptons.front().Pt() < this->LeptonPt()) return false;
//         std::vector<Jet> jets = event.Jets();
//         if (jets.size() < 4) return false;
        return true;
    }

};

}

}
