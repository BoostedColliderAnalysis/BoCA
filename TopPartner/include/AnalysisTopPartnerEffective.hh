#pragma once

#include "AnalysisTopPartner.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Top partner analysis
 *
 * \author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisEffective : public AnalysisNaturalness<Tagger>
{

public:

  AnalysisEffective() {
        this->tagger().SetAnalysisName(ProjectName());
    }

protected:

  std::string ProjectName() const final {
    return "Naturalness-Effective-" + boca::Name(this->PreCut()) + "-" + Name(DetectorGeometry::detector_type()) + "-" + boca::Name(this->Mass()) + "-remove-again";
    }

//     std::string ProcessName() const final {
//       return "Naturalness-Effective";
//     }

    void SetFiles(Tag tag) final {
        switch (tag) {
        case Tag::signal :
          this->NewFile(tag, Process::TThh);
            break;
        case Tag::background :
//             this->NewFile(tag, Process::Tth);
            this->NewFile(tag, Process::TT);
            this->NewFile(tag, Process::ttBB);
            this->NewFile(tag, Process::ttBjj);
            break;
        }
    }

private:

    int PassPreCut(Event const& , Tag ) const final {
//         Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
//         if(jets.size() < 3) return 0;
//         if(jets.at(2).pt() < this->JetPreCut()) return 0;
//
//
//         Jets particles = event.Partons().GenParticles();
//         particles = RemoveIfSoft(particles, this->PreCut());
//         Jets tops = CopyIfParticle(particles, Id::top);
//         Jets higgs = CopyIfParticle(particles, Id::higgs);
//         Jets vectors = CopyIfParticles(particles, Id::Z, Id::W);
//         Jets partner = CopyIfParticle(particles, Id::top_partner);
//         if (tag == Tag::signal && partner.size() != 1) {
//             return 0;
//         }
//         if (tops.size() < 2 || (higgs.size() < 1 && vectors.size() < 1)) {
//             return 0;
//         }
        return 1;
    }

};

}

}
