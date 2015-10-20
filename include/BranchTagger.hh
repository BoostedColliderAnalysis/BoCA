/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Tagger.hh"
#include "Singlet.hh"
#include "TClonesArray.h"
#include "Sort.hh"
#include "Vector.hh"
#include "Math.hh"
#include "Types.hh"
#include "exroot/ExRootAnalysis.hh"
#include "Debug.hh"

namespace boca
{

/**
 * @brief Tagger base class using Branch template
 *
 */
template<typename BranchTemplate>
class BranchTagger : public Tagger
{

public:

    template<typename Multiplet>
    float Bdt(Multiplet const& multiplet, TMVA::Reader const& reader) const {
        Info();
        FillBranch(multiplet);
        return Tagger::Bdt(reader);
    }

//     template <template<typename> typename Analysis, typename tagger>
//     void PreRequisits(Output output = Output::normal) {
//         Analysis<tagger> analysis;
//         Run(analysis, output);
//     }


    BranchTemplate& Branch() final {
        Info();
        return branch_;
    }

protected:

    template<typename Multiplet>
    std::vector<Multiplet> ReduceResult(std::vector<Multiplet> multiplets, size_t max = 4) const {
        Info();
        Check(multiplets.size()>=max, multiplets.size());
        if (multiplets.empty()) return multiplets;
        std::sort(multiplets.begin(), multiplets.end());
        multiplets.erase(multiplets.begin() + std::min(max, multiplets.size()), multiplets.end());
        return multiplets;
    }

    Jets ReduceResult(Jets jets, size_t max = 4) const {
        Info();
        if (jets.empty()) return jets;
        jets = SortedByBdt(jets);
        jets.erase(jets.begin() + std::min(max, jets.size()), jets.end());
        return jets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMass(std::vector<Multiplet> multiplets, Mass mass, size_t number = 1) const {
        Info();
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMassTo(multiplets, mass);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestRapidity(std::vector<Multiplet> multiplets, size_t number = 1) const {
        Info();
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMaxDeltaRap(multiplets);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMatch(std::vector<Multiplet> const& multiplets, Jets const& particles, Id id = Id::empty) const {
        Info();
        std::vector<Multiplet> close = CopyIfClose(multiplets, particles);
        close = SortedByBdt(close);
        if (id != Id::empty) close = SortedByMassTo(close, id);
//         std::cout << "close " << close.size() << "\n";
        return std::vector<Multiplet>(&close[0], &close[std::min(close.size(), particles.size())]);
    }

    template<typename Multiplet>
    std::vector<Multiplet> RemoveBestMatch(std::vector<Multiplet> const& multiplets, Jets const& particles) const {
        Info();
        return RemoveIfClose(multiplets, particles);
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMatches(std::vector<Multiplet> multiplets, Jets const& particles, Tag tag, Id id = Id::empty) const {
        Info();
        std::sort(multiplets.begin(), multiplets.end());
        switch (tag) {
        case Tag::signal :
            return BestMatch(multiplets, particles, id);
            break;
        case Tag::background  :
            return RemoveBestMatch(multiplets, particles);
            break;
        }
    }

    Jets BestMatches(Jets jets, Jets const& particles, Tag tag, Id id = Id::empty) const {
        Info();
        jets = SortedByBdt(jets);
        switch (tag) {
        case Tag::signal :
            return BestMatch(jets, particles, id);
            break;
        case Tag::background  :
            return RemoveBestMatch(jets, particles);
            break;
        }
    }

    template<typename Multiplet>
    int SaveEntries(std::vector<Multiplet> multiplets, size_t max = LargeNumber()) const {
        Info();
        if (multiplets.empty()) return 0;
        if (multiplets.size() > 1) std::sort(multiplets.begin(), multiplets.end());
        auto sum = std::min(multiplets.size(), max);
        for (auto const & counter : Range(sum)) {
            FillBranch(multiplets.at(counter));
            static_cast<BranchTemplate&>(*TreeBranch().NewEntry()) = Branch();
        }
        return sum;
    }

    int SaveEntries(std::vector<fastjet::PseudoJet> jets, size_t max = LargeNumber()) const {
        Info();
        if (jets.empty()) return 0;
        if (jets.size() > 1) jets = SortedByBdt(jets);
        auto sum = std::min(jets.size(), max);
        for (auto const & counter : Range(sum)) {
            FillBranch(Singlet(jets.at(counter)));
            static_cast<BranchTemplate&>(*TreeBranch().NewEntry()) = Branch();
        }
        return sum;
    }

    template<typename Multiplet>
    int SaveEntries(std::vector<Multiplet> multiplets, Jets particles, Tag tag, Id id = Id::empty) const {
        Info();
        return SaveEntries(BestMatches(multiplets, particles, tag, id));
    }

//     template<typename Multiplet>
//     int SaveEntries(std::vector<Multiplet> const& multiplets, Jets const& particles, Id id, Tag tag) const {
//         Jets type = CopyIfParticle(particles, id);
//         std::vector<Multiplet> matches = BestMatches(multiplets, type, tag);
//         if (matches.size() > type.size()) matches = SortedByMassTo(matches, id);
//         return SaveEntries(std::vector<Multiplet>(matches.begin(), matches.begin() + type.size()), type.size());
//     }
//
//     template<typename Multiplet>
//     int SaveEntries(std::vector<Multiplet> const& multiplets,Jets const& particles, int id, Tag tag) const {
//       Jets type = CopyIfExactParticle(particles, id);
//       std::vector<Multiplet> matches = BestMatches(multiplets, type, tag);
//       if (matches.size() > type.size()) matches = SortedByMassTo(matches, id);
//       return SaveEntries(std::vector<Multiplet>(matches.begin(), matches.begin() + type.size()), type.size());
//     }

    TClass& Class() const final {
        Info();
        return *BranchTemplate::Class();
    }

    float Bdt(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const {
        Info();
        FillBranch(Singlet(jet));
        return Tagger::Bdt(reader);
    }

    void DefineVariables() override {
        Info();
        ClearObservables();
        AddVariables();
        AddSpectators();
    }

//     template <typename Multiplet>
//     Multiplet SetBdt(Multiplet& multiplet, TMVA::Reader const& reader) {
//         multiplet.SetBdt(Bdt(multiplet, reader));
//         return multiplet;
//     }

private:

    const BranchTemplate& Branch() const final {
        Info();
        return branch_;
    }

    float ReadBdt(TClonesArray const& clones_array, int entry) const final {
        Info();
        return static_cast<BranchTemplate&>(*clones_array.At(entry)).Bdt;
    }

    void AddVariables() {
        Info();
        for (auto const & variable : Branch().Variables()) AddVariable(variable.value(), variable.name());
    }

    void AddSpectators() {
        Info();
        for (auto const & spectator : Branch().Spectators()) AddSpectator(spectator.value(), spectator.name());
    }

    template<typename Multiplet>
    void FillBranch(Multiplet const& multiplet) const {
        Info();
        branch_.Fill(multiplet);
    }

    /**
     * @brief Branch storing the analysis results
     *
     */
    mutable BranchTemplate branch_;
};

}
