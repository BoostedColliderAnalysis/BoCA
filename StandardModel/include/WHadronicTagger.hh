/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <functional>
#include "BottomTagger.hh"
#include "TaggerTemplate.hh"
#include "multiplets/Doublet.hh"
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

  using Function = std::function<boost::optional<Doublet>(Doublet&)>;

public:

    WHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, const Tag Tag) const override;

    std::vector<Doublet> Multiplets(std::vector<Jet> const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    boost::optional<Doublet> Multiplet(boca::Jet jet, const TMVA::Reader& reader) const;

    boost::optional<Doublet> Multiplet(Jet const& jet_1, Jet const& jet_2, TMVA::Reader const& reader) const;

    boost::optional<Doublet> SubMultiplet(Jet const& jet, TMVA::Reader const& reader) const;

    std::string Name() const override;

    std::string LatexName() const override;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Doublet> Doublets(Event const& event, PreCuts const& pre_cuts, Function const& function) const;

    std::vector<Doublet> Doublets(std::vector<Jet> const& jets, Function const& function) const;

    boost::optional<Doublet> CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    boost::optional<Doublet> SubDoublet(Jet const& jet, Function const& function) const;

    bool Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts) const;

    boost::optional<Doublet> Multiplet(boca::Doublet& doublet, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    Reader<BottomTagger> bottom_reader_;

    Mass w_mass_window_;
};

}

}
