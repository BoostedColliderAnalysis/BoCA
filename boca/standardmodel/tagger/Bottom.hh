/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Singlet.hh"
#include "boca/tagger/Tagger.hh"
#include "boca/standardmodel/branch/Bottom.hh"
#include "boca/external/MuXboostedBTagging.hh"


namespace boca
{

namespace standardmodel
{

/**
* @brief %Tagger
*
*/
namespace tagger
{

/**
 * @brief BDT tagger for bottom jets.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015-2016 Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
class Bottom : public Tagger<Jet, branch::Bottom>
{

public:

    Bottom();

    /**
     * @brief Train the bottom tagger with pre cuts
     */
    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    std::vector<Jet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    std::vector<Jet> Jets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader);

    /**
     * @brief calculate bottom bdt for subjets of given jet
     *
     */
    std::vector<Jet> SubMultiplet(Jet const& jet, TMVA::Reader const& reader, int sub_jet_number);

    /**
     * @brief calculate bottom bdt for given jet
     *
     */
    Jet Multiplet(Jet& jet, TMVA::Reader const& reader);

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Jet> Jets(Event const& event, PreCuts const& pre_cuts, std::function<Jet(Jet&)> const& function);

    using Tagger::Multiplets;
    std::vector<Jet> Multiplets(std::vector<Jet> jets, std::function<Jet(Jet&)> const& function, unsigned sub_jet_number = 1) const;

    bool Problematic(Jet const& jet, boca::PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Jet const& jet, boca::PreCuts const& pre_cuts) const;

    std::vector<Jet> SubJets(std::vector<Jet> const& jets, int sub_jet_number) const;

    Mass bottom_max_mass_;

    MuXboostedBTagging muon_b_tagging_;

};

}

}

template<>
inline void Tagger<Jet, standardmodel::branch::Bottom>::FillBranch(Jet const& multiplet)
{
    Branch().Fill(Singlet(multiplet));
}

}
