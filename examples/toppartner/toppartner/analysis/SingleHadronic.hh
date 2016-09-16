/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "toppartner/analysis/TopPartner.hh"
#include "toppartner/tagger/EventSingleHadronic.hh"
#include "toppartner/tagger/VetoTopPartnerLeptonic.hh"
#include "toppartner/tagger/TopPartnerLeptonicNeutral.hh"
#include "toppartner/tagger/TopPartnerHadronic.hh"
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

    std::string Name() const override {
        INFO0;
        return "Single-Hadronic-" + boca::Name(Settings::Collider()) + "-" + boca::units::Name(this->Mass()) + "-latex";
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

    bool PassPreCut(boca::Event const&) const override {
        INFO0;
//       if(tag == Tag::signal){
//        std::vector<Jet> partner = partner_tagger.Particles(event);
//         if(partner.empty()) return false;
//       }
//       static int counter = 0;
//       ++counter;
//     ERROR(counter);

//      ERROR0;
//      this->PrintGeneratorLevel(event);

//        std::vector<Jet> jets = SortedByPt(event.Jets());
//         if (jets.size() < 3) return false;
//         if (jets.at(2).Pt() < this->JetPreCut()) return false;
//
//
//        std::vector<Jet> particles = event.GenParticles();
//         particles = RemoveIfSoft(particles, this->PreCut());
//        std::vector<Jet> tops = CopyIfParticle(particles, Id::top);
//        std::vector<Jet> higgs = CopyIfParticle(particles, Id::higgs);
//        std::vector<Jet>vectors = CopyIfParticles(particles, Id::Z, Id::W);
//        std::vector<Jet> partner = CopyIfParticle(particles, Id::top_partner);
//         if (tag == Tag::signal && partner.size() != 1) {
//             return false;
//         }
//         if (tops.size() < 2 || (higgs.empty() && vectors.empty())) {
//             return false;
//         }
        return true;
    }

};

}

}
