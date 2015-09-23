#pragma once

#include "AnalysisStandardModel.hh"

namespace boca
{

namespace standardmodel
{
/**
 *
 * @brief Higgs tagger analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisBoson : public AnalysisStandardModel<Tagger>
{

public:

    AnalysisBoson() {
        this->set_tagger_analysis_name(ProjectName());
        this->pre_cuts().SetPtLowerCut(Id::higgs, this->LowerPtCut());
        this->pre_cuts().SetPtUpperCut(Id::higgs, this->UpperPtCut());
        this->pre_cuts().SetPtLowerCut(Id::bottom, this->LowerPtCut() / 5.);
        this->pre_cuts().SetPtUpperCut(Id::bottom, this->UpperPtCut() / 5.);
        this->pre_cuts().SetMassUpperCut(Id::higgs, 250. * GeV);
        this->pre_cuts().SetTrackerMaxEta(Id::higgs, DetectorGeometry::TrackerEtaMax());
        this->pre_cuts().SetTrackerMaxEta(Id::bottom, DetectorGeometry::TrackerEtaMax());
    }

private:

    std::string ProjectName() const final {
        return  Name(this->collider_type()) + "-" + boca::Name(this->LowerPtCut()) + "";
    }

    void SetFiles(Tag tag) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::hh_bb);
            if (this->tagger().Name() != "Bottom")
                this->NewFile(tag, Process::zz);
            if (this->tagger().Name() != "Bottom")
                this->NewFile(tag, Process::ww);
            if (this->tagger().Name() == "Bottom")
                this->NewFile(tag, Process::bb);
            if (this->tagger().Name() == "Bottom")
                this->NewFile(tag, Process::tt_had);
            if (this->tagger().Name() == "Bottom")
                this->NewFile(tag, Process::tt_lep);
            break;
        case Tag::background :
            if (this->tagger().Name() != "Bottom")
                this->NewFile(tag, Process::tt_had);
            if (this->tagger().Name() != "Bottom")
                this->NewFile(tag, Process::tt_lep);
            if (this->tagger().Name() != "Bottom")
                this->NewFile(tag, Process::bb);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::gg);
            break;
        }

    }

    int PassPreCut(Event const& event, Tag) const final {
        Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
        if (jets.empty()) return 0;
        if (jets.front().pt() < this->LowerPtCut() / GeV) return 0;
        Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
        if ((particles.at(0).pt() > this->LowerQuarkCut() / GeV && particles.at(0).pt() < this->UpperQuarkCut() / GeV) && (particles.at(1).pt() > this->LowerQuarkCut() / GeV &&  particles.at(1).pt() < this->UpperQuarkCut() / GeV)) return 1;
        return 0;
    }

};

}

}
