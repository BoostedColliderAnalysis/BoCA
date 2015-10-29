/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "AnalysisTopPartner.hh"
#include "EventSingleLeptonicTagger.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Top partner analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisSingleLeptonic : public AnalysisNaturalness<Tagger>
{

protected:

    std::string AnalysisName() const final {
        Info();
        return "Naturalness-Single-Leptonic-" + Name(DetectorGeometry::detector_type()) + "-" + boca::Name(this->Mass())
//                + "-revertveto";
               + "-test";
//                + "problematic";
//         + "wrong";
    }

    void SetFiles(Tag tag, Stage) final {
        Info();
        switch (tag) {
        case Tag::signal :
            if (this->template TaggerIs<TopPartnerHadronicTagger>()) this->NewFile(tag, Process::TT);
            else this->NewFile(tag, Process::TthLep);
            break;
        case Tag::background :
            if (this->template TaggerIs<TopPartnerHadronicTagger>()) this->NewFile(tag, Process::TthLep);
            else if (!this->template TaggerIs<TopPartnerLeptonicTagger>()) this->NewFile(tag, Process::TT);
            this->NewFile(tag, Process::ttBB);
            this->NewFile(tag, Process::ttBjj);
            break;
        }
    }

private:
//   TopPartnerLeptonicTagger partner_tagger_;

    int PassPreCut(Event const&, Tag) const final {
        Info();
//     if(tag == Tag::signal){
//       Jets partner = partner_tagger.Particles(event);
//       if(partner.empty()) return 0;
//     }
//         Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
//         if (jets.size() < 3) return 0;
//         if (jets.at(2).pt() < this->JetPreCut()) return 0;
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
