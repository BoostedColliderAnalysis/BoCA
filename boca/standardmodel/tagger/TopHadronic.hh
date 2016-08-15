/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <functional>
#include "boca/multiplets/Triplet.hh"
#include "boca/standardmodel/tagger/WHadronic.hh"
#include "boca/standardmodel/branch/TopHadronic.hh"

namespace boca
{

class MomentumRange;

namespace standardmodel
{

namespace tagger
{

/**
 * @brief BDT tagger for hadronically decaying top quarks
 *
 */
class TopHadronic : public Tagger<Triplet, branch::TopHadronic>
{

public:

    TopHadronic(Id id = Id::top);

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using Tagger::Multiplets;

    std::vector<Triplet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    latex::String LatexName() const override;

    std::vector<Particle> Particles(Event const& event) const;

private:

    using Function = std::function<boost::optional<Triplet>(Triplet&, std::vector<Jet> const&)>;

    std::vector<Triplet> ThreeJets(const std::vector< boca::Jet >& jets, const std::vector< boca::Lepton >& leptons, const Function& function, const boca::MomentumRange& range);

    std::vector<Triplet> TwoJets(const std::vector< boca::Jet >& jets, boca::Jet const& jet, const std::vector< boca::Lepton >& leptons, const Function& function, const boca::MomentumRange& range);

    std::vector<Triplet> ThreeSubJets(boca::Jet const& jet, const std::vector< boca::Lepton >& leptons, const Function& function, const boca::MomentumRange& range);

    std::vector<Triplet> TwoSubJets(boca::Jet const& jet, const std::vector< boca::Lepton >& leptons, const Function& function, const boca::MomentumRange& range);

    boost::optional<Triplet> HighlyBoosted(Jet const& jet, std::vector<Lepton> const& leptons, Function const& function) const;

    boost::optional<Triplet> Tripple(Doublet const& doublet, Jet const& jet, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range, bool check_overlap = false) const;

    boost::optional<Triplet> Tripple(Triplet& triplet, std::vector<Lepton> const& leptons, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<Triplet> Triplets(Event const& event, Function const& function);

    std::vector<Triplet> Triplets(std::vector<Doublet> const& doublets, std::vector<Jet> const& jets, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const;

    std::vector<Triplet> Triplets(Doublet const& doublet, std::vector<Jet> const& jets, std::vector<Lepton> const& leptons, Function const& function, MomentumRange const& range) const;

    boost::optional<Triplet> Multiplet(Triplet& triplet, std::vector<Lepton> const& leptons, PreCuts const& pre_cuts, TMVA::Reader const& reader);

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const;

    Reader<tagger::Bottom> bottom_reader_;

    Reader<tagger::WHadronic> w_hadronic_reader_;

    Mass top_mass_window_;

    Id id_;

};

}

}

}
