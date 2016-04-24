/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>
#include "boca/standardmodel/BottomTagger.hh"
#include "boca/TaggerTemplate.hh"
#include "boca/multiplets/Doublet.hh"
#include "boca/multivariant/Reader.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief BDT tagger for hadronically decaying W bosons
 *
 */
class WHadronicTagger : public TaggerTemplate<Doublet, WHadronicBranch>
{

  using Function = std::function<boost::optional<Doublet>(Doublet&)>;

public:

    WHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag Tag) override;

    using TaggerTemplate::Multiplets;

    std::vector<Doublet> Multiplets(std::vector<Jet> const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    boost::optional<Doublet> Multiplet(const boca::Jet& jet, const TMVA::Reader& reader);

    boost::optional<Doublet> Multiplet(Jet const& jet_1, Jet const& jet_2, TMVA::Reader const& reader);

    boost::optional<Doublet> SubMultiplet(Jet const& jet, TMVA::Reader const& reader);

    std::string Name() const override;

    std::string LatexName() const override;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Doublet> Doublets(Event const& event, PreCuts const& pre_cuts, Function const& function);

    std::vector<Doublet> Doublets(std::vector<Jet> const& jets, Function const& function) const;

    boost::optional<Doublet> CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    boost::optional<Doublet> SubDoublet(const boca::Jet& jet, const Function& function);

    bool Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(boca::Doublet const& doublet, boca::PreCuts const& pre_cuts) const;

    boost::optional<Doublet> Multiplet(boca::Doublet& doublet, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader);

    Reader<BottomTagger> bottom_reader_;

    Mass w_mass_window_;
};

}

}
