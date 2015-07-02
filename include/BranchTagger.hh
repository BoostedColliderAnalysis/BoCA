#pragma once

#include "Tagger.hh"
#include "Singlet.hh"
#include "TClonesArray.h"

namespace analysis
{


template<typename Branch>
class BranchTagger : public Tagger
{

protected:

//     BranchTagger() {
//         DefineVariables();
//     }

    template<typename Multiplet>
    std::vector<Multiplet> ReduceResult(std::vector<Multiplet> &multiplets, const std::size_t max = 4) {
//         multiplets.erase(std::remove_if(multiplets.begin(), multiplets.end(), [&](Multiplet & multiplet) {
//             return multiplet.IsEmpty();
//         }), multiplets.end());
        if (multiplets.empty()) return multiplets;
        std::sort(multiplets.begin(), multiplets.end());
        multiplets.erase(multiplets.begin() + std::min(max, multiplets.size()), multiplets.end());
        return multiplets;
    }

    Jets ReduceResult(Jets &jets, const std::size_t max = 4) {
        if (jets.empty()) return jets;
        std::sort(jets.begin(), jets.end(), SortByBdt());
        jets.erase(jets.begin() + std::min(max, jets.size()), jets.end());
        return jets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMass(std::vector<Multiplet> &multiplets, const float mass, const std::size_t number = 1) {
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMassTo(multiplets, mass);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestRapidity(std::vector<Multiplet> &multiplets, const std::size_t number = 1) {
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortByMaxDeltaRap(multiplets);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMatch(std::vector<Multiplet> &multiplets, const Jets &particles) {
        if (multiplets.size() <= particles.size()) return multiplets;
        return CopyIfClose(multiplets, particles);
    }

    template<typename Multiplet>
    std::vector<Multiplet> RemoveBestMatch(std::vector<Multiplet> &multiplets, const Jets &particles) {
        if (multiplets.size() <= particles.size()) return multiplets;
        return RemoveIfClose(multiplets, particles);
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMatches(std::vector<Multiplet> &multiplets, const Jets &particles, const Tag tag) {
//         multiplets.erase(std::remove_if(multiplets.begin(), multiplets.end(), [&](Multiplet & multiplet) {
//             return multiplet.IsEmpty();
//         }), multiplets.end());
        std::sort(multiplets.begin(), multiplets.end());
        switch (tag) {
        case Tag::signal :
            return BestMatch(multiplets, particles);
            break;
        case Tag::background  :
            return RemoveBestMatch(multiplets, particles);
            break;
        }
    }

    Jets BestMatches(Jets &jets, const Jets &particles, const Tag tag) {
        std::sort(jets.begin(), jets.end(), SortByBdt());
        switch (tag) {
        case Tag::signal :
            return BestMatch(jets, particles);
            break;
        case Tag::background  :
            return RemoveBestMatch(jets, particles);
            break;
        }
    }

    template<typename Multiplet>
    int SaveEntries(const std::vector<Multiplet> &multiplets, std::size_t max = LargeNumber()) {
        if (multiplets.empty()) return 0;
//         std::sort(multiplets.begin(),multiplets.end());
        const int sum = std::min(multiplets.size(), max);
        for (int counter = 0 ; counter < sum; ++counter) {
            FillBranch(multiplets.at(counter));
            static_cast<Branch &>(*tree_branch().NewEntry()) = branch();
        }
        return sum;
    }

    int SaveEntries(const std::vector<fastjet::PseudoJet> &jets, std::size_t max = LargeNumber()) {
        if (jets.empty()) return 0;
        const int sum = std::min(jets.size(), max);
        for (int counter = 0 ; counter < sum; ++counter) {
            FillBranch(Singlet(jets.at(counter)));
            static_cast<Branch &>(*tree_branch().NewEntry()) = branch();
        }
        return jets.size();
    }

//     int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
//       return SaveEntries(Multiplets(event,pre_cuts, reader));
//     }

    TClass &Class() const {
        return *Branch::Class();
    }

    Branch &branch() {
        return branch_;
    }

    float ReadBdt(const TClonesArray &clones_array, const int entry) const {
        return static_cast<Branch &>(*clones_array.At(entry)).Bdt;
//         return dynamic_cast<Branch &>(*clones_array.At(entry)).Bdt;
    }

    template<typename Multiplet>
    float Bdt(const Multiplet &multiplet, const TMVA::Reader &reader) {
        FillBranch(multiplet);
        return Tagger::Bdt(reader);
    }

    float Bdt(const fastjet::PseudoJet &jet, const TMVA::Reader &reader) {
        FillBranch(Singlet(jet));
        return Tagger::Bdt(reader);
    }

    virtual void DefineVariables() {
//         Info("Define Variables");
        ClearObservables();
        AddVariables();
        AddSpectators();
    }

//     auto Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);
//
//     int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
//       return SaveEntries(Multiplets(event, pre_cuts, reader));
//     }

private:

    void AddVariables() {
        for (auto & variable : branch().Variables()) {
            AddVariable(variable.first, variable.second);
        }
    }

    void AddSpectators() {
        for (auto & spectator : branch().Spectators()) {
            AddSpectator(spectator.first, spectator.second);
        }
    }

    template<typename Multiplet>
    void FillBranch(const Multiplet &multiplet) {
//         Info("Fill Branch");
        branch_.Fill(multiplet);
    }

    /**
     * @brief Branch saving the analysis results
     *
     */
    Branch branch_;
};

}
