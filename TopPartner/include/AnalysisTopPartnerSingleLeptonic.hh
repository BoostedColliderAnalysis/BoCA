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
        Info0;
        return "Single-Leptonic-" + Name(DetectorGeometry::detector_type()) + "-" + boca::Name(this->Mass()) + "-dipolarity";
    }

    void SetFiles(Tag tag, Stage) final {
        Info0;
        switch (tag) {
        case Tag::signal :
            if (this->template TaggerIs<VetoTopPartnerHadronicTagger>()) this->NewFile(tag, Process::TT);
            else this->NewFile(tag, Process::TthLep);
            break;
        case Tag::background :
            if (this->template TaggerIs<VetoTopPartnerHadronicTagger>()) this->NewFile(tag, Process::TthLep);
            else if (!this->template TaggerIs<TopPartnerLeptonicTagger>()) this->NewFile(tag, Process::TT);
            if (!this->template TaggerIs<VetoTopPartnerHadronicTagger>()) {
                this->NewFile(tag, Process::ttBB);
                this->NewFile(tag, Process::ttBjj);
            }
            break;
        }
    }

private:
//   TopPartnerLeptonicTagger partner_tagger_;

    int PassPreCut(Event const&, Tag) const final {
        Info0;
//     if(tag == Tag::signal){
//      std::vector<Jet> partner = partner_tagger.Particles(event);
//       if(partner.empty()) return 0;
//     }
//        std::vector<Jet> jets = SortedByPt(event.Hadrons().Jets());
//         if (jets.size() < 3) return 0;
//         if (jets.at(2).Pt() < this->JetPreCut()) return 0;
//
//
//        std::vector<Jet> particles = event.Partons().GenParticles();
//         particles = RemoveIfSoft(particles, this->PreCut());
//        std::vector<Jet> tops = CopyIfParticle(particles, Id::top);
//        std::vector<Jet> higgs = CopyIfParticle(particles, Id::higgs);
//        std::vector<Jet>vectors = CopyIfParticles(particles, Id::Z, Id::W);
//        std::vector<Jet> partner = CopyIfParticle(particles, Id::top_partner);
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
