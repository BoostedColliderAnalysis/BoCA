/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "AnalysisTopPartner.hh"
#include "EventSingleLeptonicTagger.hh"
#include "TopPartnerHadronicNeutralTagger.hh"
#include "DEBUG.hh"

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

    std::string AnalysisName() const override {
        INFO0;
        return "Single-Leptonic-" + Name(DetectorGeometry::DetectorType()) + "-" + boca::Name(this->Mass()) + "-new-higgs";
    }

    void SetFiles(Tag tag, Stage)override {
        INFO0;
        switch (tag) {
        case Tag::signal :
            if (this->template TaggerIs<VetoTopPartnerHadronicTagger>() || this->template TaggerIs<TopPartnerHadronicNeutralTagger>()) this->NewFile(tag, Process::TT);
            else this->NewFile(tag, Process::TthLep);
            break;
        case Tag::background :
            if (this->template TaggerIs<VetoTopPartnerHadronicTagger>() || this->template TaggerIs<TopPartnerHadronicNeutralTagger>()) this->NewFile(tag, Process::TthLep);
            else if (!this->template TaggerIs<TopPartnerLeptonicNeutralTagger>()) this->NewFile(tag, Process::TT);
            if (!this->template TaggerIs<VetoTopPartnerHadronicTagger>() || this->template TaggerIs<TopPartnerHadronicNeutralTagger>()) {
                this->NewFile(tag, Process::ttBB);
                this->NewFile(tag, Process::ttBjj);
            }
            break;
        }
    }

private:
//   TopPartnerLeptonicNeutralTagger partner_tagger_;

    int PassPreCut(Event const&, Tag) const override {
        INFO0;
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
//         if (tops.size() < 2 || (higgs.empty() && vectors.empty())) {
//             return 0;
//         }
        return 1;
    }

};

}

}
