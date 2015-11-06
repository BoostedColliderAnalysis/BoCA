/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "TClonesArray.h"

#include "exroot/ExRootAnalysis.hh"

#include "Sort.hh"
#include "Tagger.hh"
#include "Singlet.hh"
#include "PreCuts.hh"
// #define INFORMATION
// #include "Debug.hh"

namespace boca
{

/**
 * @brief Tagger base class using Branch template
 *
 */
template<typename MultipletTemplate, typename BranchTemplate>
class TaggerTemplate : public Tagger
{

public:

    float Bdt(MultipletTemplate const& multiplet, TMVA::Reader const& reader) const {
//         Info0;
        FillBranch(multiplet);
        return Tagger::Bdt(reader);
    }

//     void PreRequisits(Output output = Output::normal) {
//         Analysis<tagger> analysis;
//         Run(analysis, output);
//     }

    BranchTemplate& Branch() final {
//         Info0;
        return branch_;
    }

    int SaveBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

protected:

    std::vector<MultipletTemplate> ReduceResult(std::vector<MultipletTemplate> multiplets, size_t max = 4) const {
//         Info0;
//         DebugCheck(multiplets.size() >= max, multiplets.size());
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        multiplets.erase(multiplets.begin() + std::min(max, multiplets.size()), multiplets.end());
        return multiplets;
    }

    std::vector<MultipletTemplate> BestMass(std::vector<MultipletTemplate> multiplets, Mass mass, size_t number = 1) const {
//         Info0;
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMassTo(multiplets, mass);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    std::vector<MultipletTemplate> BestRapidity(std::vector<MultipletTemplate> multiplets, size_t number = 1) const {
//         Info0;
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMaxDeltaRap(multiplets);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename T>
    std::vector<T> BestMatch(std::vector<T> const& multiplets, Jets const& particles, Id id = Id::empty) const {
//         Info(multiplets.size(), particles.size());
        std::vector<T> close = CopyIfClose(multiplets, particles);
//         Info(close.size());
        close = SortedByBdt(close);
        if (id != Id::empty) close = SortedByMassTo(close, id);
        return std::vector<T>(&close[0], &close[std::min(close.size(), particles.size())]);
    }

    template<typename T>
    std::vector<T> RemoveBestMatch(std::vector<T> const& multiplets, Jets const& particles) const {
//         Info(multiplets.size());
        return RemoveIfClose(multiplets, particles);
    }

    template<typename T>
    std::vector<T> BestMatches(std::vector<T> multiplets, Jets const& particles, Tag tag, Id id = Id::empty) const {
//         Info(multiplets.size());
        multiplets = SortedByBdt(multiplets);
        switch (tag) {
        case Tag::signal : return BestMatch(multiplets, particles, id);
        case Tag::background  : return RemoveBestMatch(multiplets, particles);
        default : return multiplets;
        }
    }

    int SaveEntries(std::vector<MultipletTemplate> multiplets, size_t max = LargeNumber()) const {
//         Info(multiplets.size());
        if (multiplets.empty()) return 0;
        if (multiplets.size() > 1) multiplets = SortedByBdt(multiplets);
        auto sum = std::min(multiplets.size(), max);
        for (auto const & counter : Range(sum)) {
            FillBranch(multiplets.at(counter));
            std::lock_guard<std::mutex> guard(mutex_);
            static_cast<BranchTemplate&>(*TreeBranch().NewEntry()) = Branch();
        }
        return sum;
    }

    int SaveEntries(std::vector<MultipletTemplate> multiplets, Jets particles, Tag tag, Id id = Id::empty) const {
//         Info(multiplets.size());
        return SaveEntries(BestMatches(multiplets, particles, tag, id));
    }

    int SaveEntries(std::vector<MultipletTemplate> multiplets, Tag tag) const {
        switch (tag) {
        case Tag::signal : return SaveEntries(multiplets, 1);
        case Tag::background : return SaveEntries(multiplets);
        default : return {};
        }
    }

//
//     int SaveEntries(std::vector<MultipletTemplate> const& multiplets, Jets const& particles, Id id, Tag tag) const {
//         Jets type = CopyIfParticle(particles, id);
//         std::vector<MultipletTemplate> matches = BestMatches(multiplets, type, tag);
//         if (matches.size() > type.size()) matches = SortedByMassTo(matches, id);
//         return SaveEntries(std::vector<MultipletTemplate>(matches.begin(), matches.begin() + type.size()), type.size());
//     }
//
//
//     int SaveEntries(std::vector<MultipletTemplate> const& multiplets,Jets const& particles, int id, Tag tag) const {
//       Jets type = CopyIfExactParticle(particles, id);
//       std::vector<MultipletTemplate> matches = BestMatches(multiplets, type, tag);
//       if (matches.size() > type.size()) matches = SortedByMassTo(matches, id);
//       return SaveEntries(std::vector<MultipletTemplate>(matches.begin(), matches.begin() + type.size()), type.size());
//     }

    TClass& Class() const final {
//         Info0;
        return *BranchTemplate::Class();
    }

    void DefineVariables() override {
//         Info0;
        ClearObservables();
        AddVariables();
        AddSpectators();
    }

//     MultipletTemplate SetBdt(MultipletTemplate& multiplet, TMVA::Reader const& reader) {
//         multiplet.SetBdt(Bdt(multiplet, reader));
//         return multiplet;
//     }

    virtual std::vector<MultipletTemplate> Multiplets(Event const&, PreCuts const&, TMVA::Reader const&) const = 0;

    std::vector<MultipletTemplate> Multiplets(Event const& event, TMVA::Reader const& reader) const {
//       Info0;
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    };

private:

    const BranchTemplate& Branch() const final {
//         Info0;
        return branch_;
    }

    float ReadBdt(TClonesArray const& clones_array, int entry) const final {
//         Info0;
        return static_cast<BranchTemplate&>(*clones_array.At(entry)).Bdt;
    }

    void AddVariables() {
//         Info0;
        for (auto const & variable : Branch().Variables()) AddVariable(variable.value(), variable.name());
    }

    void AddSpectators() {
//         Info0;
        for (auto const & spectator : Branch().Spectators()) AddSpectator(spectator.value(), spectator.name());
    }

    void FillBranch(MultipletTemplate const& multiplet) const {
//         Info0;
        branch_.Fill(multiplet);
    }


    /**
     * @brief Branch storing the analysis results
     *
     */
    mutable BranchTemplate branch_;

};

}
// #undef INFORMATION

