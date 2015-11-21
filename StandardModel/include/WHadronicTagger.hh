/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>
#include "BottomTagger.hh"
#include "TaggerTemplate.hh"
#include "Doublet.hh"
#include "Reader.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief W BDT tagger
 *
 */
class WHadronicTagger : public TaggerTemplate<Doublet, WHadronicBranch>
{

public:

    WHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, const Tag Tag) const final;

    std::vector<Doublet> Multiplets(Jets const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    boost::optional<Doublet> Multiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const;

    boost::optional<Doublet> Multiplet(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2, TMVA::Reader const& reader) const;

    boost::optional<Doublet> SubMultiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const;

    std::string Name() const final;

    std::string NiceName() const final;

private:

    Jets Particles(Event const& event) const;

    std::vector<Doublet> Doublets(Event const& event, PreCuts const& pre_cuts, std::function<boost::optional<Doublet>(Doublet&)> const& function) const;

    std::vector<Doublet> Doublets(Jets const& jets, std::function<boost::optional<Doublet>(Doublet&)> const& function) const;

    boost::optional<Doublet> CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    boost::optional<Doublet> SubDoublet(fastjet::PseudoJet const& jet, std::function<boost::optional<Doublet>(Doublet&)> const& function) const;

    bool Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts) const;

    boost::optional<Doublet> Multiplet(boca::Doublet& doublet, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    Reader<BottomTagger> bottom_reader_;

    Mass w_mass_window_;
};

}

}
