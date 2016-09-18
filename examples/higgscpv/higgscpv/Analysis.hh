#pragma once

#include "boca/EventShapes.hh"
#include "boca/analysis/Analysis.hh"
#include "standardmodel/tagger/TopLeptonic.hh"
#include "boca/generic/DEBUG_MACROS.hh"

/**
 * @brief CP-violating Higgs couplings
 * @ingroup Examples
 *
 */
namespace higgscpv
{

using namespace boca;

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * \author Jan Hajer
 *
 */
template <typename Tagger_>
class Analysis : public boca::Analysis<Tagger_>
{

public:

    Analysis()
    {
        Settings::SetCollider(Collider::lhc);
//         this->PreCuts().PtLowerCut().Set(Id::higgs,200);
        //         this->PreCuts().MassLowerCut().Set(Id::higgs,105);
//         this->PreCuts().MassUpperCut().Set(Id::higgs,145);
        this->PreCuts().MassLowerCut().Set(Id::higgs, 50_GeV);
        this->PreCuts().MassUpperCut().Set(Id::higgs, 150_GeV);
        this->PreCuts().SetSemiLeptonic(false);
//         NoHiggs(-1);
//         SingleHiggs(-1);
    }

protected:

private:

    std::string Name() const override
    {
        return  "CPV-after-tahoe";
    }

    void SetFiles(Phase const &phase) override
    {
        switch (phase.Tag()) {
    case Tag::signal :
        // this->AddSignal("gg-tth", 0.0098);
        this->AddSignal("pp-tth", "tth", 0.02267_pb);
            //  this->AddSignal("pp-ttx0-bbbbllnunu-1", 0.02071);
            //  this->AddSignal("pp-ttx0-bbbbllnunu-1", 0.008937);
            //  this->AddSignal("pp-ttx0-bbbbllnunu-0.5", 0.01193);
            break;
        case Tag::background :
            this->AddBackground("pp-ttbb", "ttbb", 0.1266_pb);
            // this->AddBackground("pp-ttbb-bbbbllnunu", 3.457);
            break;
        }
    }

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    long TrainNumberMax() const override
    {
        return 1000;
        return 5000;
        return 10000;
        return 100;
        return 10;
    }

    bool PassPreCut(boca::Event const &event) const override
    {
        //         if(this->template TaggerIs<tagger::WLeptonic>()) return false;
        //         if(this->template TaggerIs<TopLeptonicTagger>()) static_cast<TopLeptonicTagger&>(this->()).semi_leptonic = false;
        std::vector<Lepton> leptons = SortedByPt(event.Leptons());
        if (leptons.size() < 2) return false;
//         if (leptons.at(1).Pt() < 40) return false;
//        std::vector<Jet> jets = event.Jets();
//        std::vector<Jet>gen_particles = event.GenParticles();
//        std::vector<Jet> higgs = CopyIfParticles(gen_particles, Id::CP_violating_higgs, Id::higgs);
//         if (higgs.empty()) {
//         ERROR(NoHiggs(), higgs.size());
//             return true;
//         }
//         if(higgs.front().Pt() < 200) return false;
//         static int pre_cut=0;
//         ++pre_cut;
//         ERROR(pre_cut);
//         Particle particle = higgs.front().Info().constituents().front().family().Particle();
//         Particle mother1 = higgs.front().Info().constituents().front().family().Mother();
//         Particle mother2 = higgs.front().Info().constituents().front().family().mother_2();
//         Particle grand_mother = higgs.front().Info().constituents().front().family().GrandMother();
// //         ERROR(particle.Id(),mother1.Id(),mother2.Id(),grand_mother.Id());
//         higgs = RemoveIfSingleMother(higgs);
//         ERROR(SingleHiggs(), higgs.size());
//         return higgs.size();
        return true;
    }


//     std::string FilePath() const override {
//         return this->WorkingPath();
//         return "~/Projects/HiggsCpv/Analysis/";
//         return "/Users/jingren/HEP/Research/JanH/tth-analysis/";
//     }


//     static int NoHiggs(int zero = -10) {
//         static int i = -1;
//         if (zero != -10) i = zero;
//         ++i;
//         return i;
//     }
//
//     static int SingleHiggs(int zero = -10) {
//         static int j = -1;
//         if (zero != -10) j = zero;
//         ++j;
//         return j;
//     }

};

}

