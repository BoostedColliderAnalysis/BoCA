#pragma once

#include "standardmodel/analysis/StandardModel.hh"
#include "standardmodel/tagger/Bottom.hh"

namespace standardmodel
{

namespace analysis
{

/**
 *
 * @brief Higgs tagger analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class Higgs : public StandardModel<Tagger_>
{

public:

    Higgs() {
        this->PreCuts().PtLowerCut().Set(Id::higgs, this->LowerPtCut());
        this->PreCuts().PtUpperCut().Set(Id::higgs, this->UpperPtCut());
//         this->PreCuts().PtLowerCut().Set(Id::bottom, this->LowerPtCut() / 5.);
//         this->PreCuts().PtUpperCut().Set(Id::bottom, this->UpperPtCut() / 5.);
//         this->PreCuts().MassUpperCut().Set(Id::higgs, 250_GeV);
        this->PreCuts().TrackerMaxEta().Set(Id::higgs, Settings::TrackerEtaMax());
        this->PreCuts().TrackerMaxEta().Set(Id::bottom, Settings::TrackerEtaMax());
    }

private:

    std::string Name() const override {
        return boca::Name(this->Collider()) + "-" + boca::units::Name(this->LowerPtCut()) + "-jet-1";
    }

    void SetFiles(Tag tag, Stage)override {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::hh_bb);
            if (this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::tt_had);
            if (this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::bb);
            if (this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::tt_lep);
            break;
        case Tag::background :
            if (!this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::tt_had);
            if (!this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::bb);
            if (!this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::tt_lep);
            this->NewFile(tag, Process::zz);
            this->NewFile(tag, Process::gg);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::ww);
            break;
        }
    }

    bool PassPreCut(boca::Event const&) const override {
          return true;
//        std::vector<Jet> jets = SortedByPt(event.Jets());
//         if (jets.size() < 2) return false;
//         if ((jets.at(0).Pt() > this->LowerPtCut() && jets.at(0).Pt() < this->UpperPtCut()) &&
//           (jets.at(1).Pt() > this->LowerPtCut() && jets.at(1).Pt() < this->UpperPtCut())) return true;
        return false;
    }

};

}

}
