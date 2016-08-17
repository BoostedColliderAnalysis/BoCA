/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "include/analysis/TopPartner.hh"
#include "include/tagger/EventSingleHadronic.hh"
#include "include/tagger/VetoTopPartnerLeptonic.hh"
#include "include/tagger/TopPartnerLeptonicNeutral.hh"
#include "include/tagger/TopPartnerHadronic.hh"
#define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner
{

namespace analysis
{

/**
 *
 * @brief Top partner analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class SingleHadronic : public TopPartner<Tagger_>
{

protected:

    std::string AnalysisName() const override {
        INFO0;
        return "Single-Hadronic-" + Name(Settings::Collider()) + "-" + boca::units::Name(this->Mass()) + "-latex";
    }

    void SetFiles(Tag tag, Stage)override {
        INFO0;
        switch (tag) {
        case Tag::signal :
            if (this->template TaggerIs<tagger::VetoTopPartnerLeptonic>() || this->template TaggerIs<tagger::TopPartnerLeptonicNeutral>()) this->NewFile(tag, Process::TT);
            else this->NewFile(tag, Process::TthHad);
            break;
        case Tag::background :
            if (this->template TaggerIs<tagger::VetoTopPartnerLeptonic>() || this->template TaggerIs<tagger::TopPartnerLeptonicNeutral>()) this->NewFile(tag, Process::TthHad);
            else if (!this->template TaggerIs<tagger::TopPartnerHadronic>()) {
                this->NewFile(tag, Process::TT);
//             if (!this->template TaggerIs<VetoTopPartnerLeptonic>() || !this->template TaggerIs<TopPartnerLeptonicNeutral>()) {
                this->NewFile(tag, Process::ttBB);
                this->NewFile(tag, Process::ttBjj);
            }
            break;
        }
    }

private:
//         TopPartnerHadronicTagger partner_tagger;

    int PassPreCut(boca::Event const& , Tag) const override {
        INFO0;
//       if(tag == Tag::signal){
//        std::vector<Jet> partner = partner_tagger.Particles(event);
//         if(partner.empty()) return 0;
//       }
//       static int counter = 0;
//       ++counter;
//     ERROR(counter);

//      ERROR0;
//      this->PrintGeneratorLevel(event);

//        std::vector<Jet> jets = SortedByPt(event.Jets());
//         if (jets.size() < 3) return 0;
//         if (jets.at(2).Pt() < this->JetPreCut()) return 0;
//
//
//        std::vector<Jet> particles = event.GenParticles();
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
