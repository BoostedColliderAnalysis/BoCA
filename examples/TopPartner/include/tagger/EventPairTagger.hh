#pragma once

#include "boca/GlobalTagger.hh"
#include "boca/multiplets/EventMultiplet.hh"
#include "boca/analysis/AnalysisBase.hh"

#include "include/tagger/TopPartnerPairTagger.hh"
#include "include/branch/NewEvent4.hh"

namespace toppartner
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventPairTagger : public Tagger<EventMultiplet<Decuplet55>, branch::NewEvent4>
{

public:

    int Train(boca::Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<EventMultiplet<Decuplet55>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<EventMultiplet<Decuplet55>> Events(boca::Event const& event, std::function<EventMultiplet<Decuplet55>(boca::EventMultiplet<Decuplet55> &)> const& function);

    Reader<TopPartnerPairTagger> signature_reader_;

    Reader<GlobalTagger> global_reader_;

};

}
