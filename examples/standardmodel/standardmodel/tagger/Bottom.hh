/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "mubtag/MuXboostedBTagging.hh"
#include "boca/tagger/Tagger.hh"
#include "boca/multiplets/Singlet.hh"

#include "standardmodel/branch/Bottom.hh"

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
class Bottom : public boca::Tagger<boca::Jet, branch::Bottom>
{

public:

    Bottom();

    /**
     * @brief Train the bottom tagger with pre cuts
     */
    int Train(boca::Event const &event, PreCuts const &pre_cuts, Tag tag) override;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    std::vector<boca::Jet> Multiplets(boca::Event const &event, PreCuts const &pre_cuts, TMVA::Reader const &reader) override;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    std::vector<boca::Jet> Jets(boca::Event const &event, PreCuts const &pre_cuts, TMVA::Reader const &reader);

    /**
     * @brief calculate bottom bdt for subjets of given jet
     *
     */
    std::vector<boca::Jet> SubMultiplet(boca::Jet const &jet, TMVA::Reader const &reader, int sub_jet_number);

    /**
     * @brief calculate bottom bdt for given jet
     *
     */
    boca::Jet Multiplet(boca::Jet &jet, TMVA::Reader const &reader);

    std::string Name() const override;

    latex::String LatexName() const override;

private:

    std::vector<Particle> Particles(boca::Event const &event) const;

    std::vector<boca::Jet> Jets(boca::Event const &event, PreCuts const &pre_cuts, std::function<boca::Jet(boca::Jet &)> const &function);

    using Tagger::Multiplets;
    std::vector<boca::Jet> Multiplets(std::vector<boca::Jet> jets, std::function<boca::Jet(boca::Jet &)> const &function, unsigned sub_jet_number = 1) const;

    bool Problematic(boca::Jet const &jet, boca::PreCuts const &pre_cuts, Tag tag) const;

    bool Problematic(boca::Jet const &jet, boca::PreCuts const &pre_cuts) const;

    std::vector<boca::Jet> SubJets(std::vector<boca::Jet> const &jets, int sub_jet_number) const;

    Mass bottom_max_mass_;

    MuXboostedBTagging muon_b_tagging_;

};

}

}

namespace boca
{

template<>
inline void Tagger<Jet, standardmodel::branch::Bottom>::FillBranch(Jet const &multiplet)
{
    Branch().Fill(Singlet(multiplet));
}

}
