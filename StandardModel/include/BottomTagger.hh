/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "BranchesSm.hh"
#include "TaggerTemplate.hh"


namespace boca
{

namespace standardmodel
{

/**
 * @brief Derived Tagger class for bottom jets.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015 Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
class BottomTagger : public TaggerTemplate<Jet, BottomBranch>
{

public:

    BottomTagger();

    /**
     * @brief Train the bottom tagger with pre cuts
     */
    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    std::vector<Jet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    std::vector<Jet> Jets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    /**
     * @brief calculate bottom bdt for subjets of given jet
     *
     */
    std::vector<Jet> SubMultiplet(Jet const& jet, TMVA::Reader const& reader, int sub_jet_number) const;

    /**
     * @brief calculate bottom bdt for given jet
     *
     */
    Jet Multiplet(Jet & jet, TMVA::Reader const& reader) const;

    std::string Name() const final;

    std::string NiceName() const final;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Jet> Jets(Event const& event, PreCuts const& pre_cuts, std::function<Jet(Jet&)> const& function) const;

    std::vector<Jet> Multiplets(std::vector<Jet> jets, std::function<Jet(Jet&)> const& function, unsigned sub_jet_number = 1) const;

    bool Problematic(Jet const& jet, boca::PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Jet const& jet, boca::PreCuts const& pre_cuts) const;

    std::vector<Jet> SubJets(std::vector<Jet> const& jets, int sub_jet_number) const;

    Mass bottom_max_mass_;

};

}

template<>
inline void TaggerTemplate<Jet, standardmodel::BottomBranch>::FillBranch(Jet const& multiplet) const
{
    //     Info0;
    branch_.Fill(Singlet(multiplet));
}


}
