/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

// #include "TClonesArray.h"

#include "exroot/ExRootAnalysis.hh"

#include "Sort.hh"
#include "Tagger.hh"
#include "PreCuts.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

/**
 * @brief Tagger base class using Branch template
 *
 */
template<typename Multiplet, typename Branch_T>
class TaggerTemplate : public Tagger
{

public:

    float Bdt(Multiplet const& multiplet, TMVA::Reader const& reader) const {
        Info0;
        FillBranch(multiplet);
        return Tagger::Bdt(reader);
    }

    bool Cut(Multiplet const& multiplet, TMVA::Reader const& reader, float effeciency) const {
        Info0;
        FillBranch(multiplet);
        return Tagger::Cut(reader, effeciency);
    }

    std::vector<bool> Cuts(Multiplet const& multiplet, TMVA::Reader const& reader) const {
        Info0;
        FillBranch(multiplet);
        std::vector<bool> passed;
        int steps = 50;
        // TODO why is this a 2?
        for (auto const & effeciency : Range(2, steps)) passed.emplace_back(Tagger::Cut(reader, float(effeciency) / steps));
        return passed;
    }

    Branch_T& Branch() final {
        Info0;
        return branch_;
    }

    int SaveBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const final {
        Info0;
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

protected:

    std::vector<Multiplet> ReduceResult(std::vector<Multiplet> multiplets, size_t max = 4) const {
        Info0;
        // DebugCheck(multiplets.size() >= max, multiplets.size());
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        multiplets.erase(multiplets.begin() + std::min(max, multiplets.size()), multiplets.end());
        return multiplets;
    }

    std::vector<Multiplet> BestRapidity(std::vector<Multiplet> multiplets, size_t number = 1) const {
        Info0;
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMaxDeltaRap(multiplets);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename Multiplet_2>
    std::vector<Multiplet_2> BestMatch(std::vector<Multiplet_2> const& multiplets, std::vector<Particle> const& particles, Id id = Id::empty) const {
        INFO(multiplets.size(), particles.size());
        std::vector<Multiplet_2> close = CopyIfClose(multiplets, particles);
        // INFO(close.size());
        close = SortedByBdt(close);
        if (id != Id::empty) close = SortedByMassTo(close, id);
        return std::vector<Multiplet_2>(&close[0], &close[std::min(close.size(), particles.size())]);
    }

    template<typename Multiplet_2>
    std::vector<Multiplet_2> RemoveBestMatch(std::vector<Multiplet_2> const& multiplets, std::vector<Particle> const& particles) const {
        INFO(multiplets.size());
        return RemoveIfClose(multiplets, particles);
    }

    template<typename Multiplet_2>
    std::vector<Multiplet_2> BestMatches(std::vector<Multiplet_2> multiplets, std::vector<Particle> const& particles, Tag tag, Id id = Id::empty) const {
        INFO(multiplets.size());
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        switch (tag) {
        case Tag::signal : return BestMatch(multiplets, particles, id);
        case Tag::background : return RemoveBestMatch(multiplets, particles);
        default : return multiplets;
        }
    }

    int SaveEntries(std::vector<Multiplet> multiplets, int max = std::numeric_limits<int>::max()) const {
        INFO(multiplets.size());
        if (multiplets.empty()) return 0;
        if (multiplets.size() > 1) multiplets = SortedByBdt(multiplets);
        auto sum = std::min(int(multiplets.size()), max);
        for (auto const & counter : Range(sum)) {
            FillBranch(multiplets.at(counter));
            std::lock_guard<std::mutex> guard(mutex_);
            static_cast<Branch_T&>(*TreeBranch().NewEntry()) = Branch();
        }
        return sum;
    }

    int SaveEntries(std::vector<Multiplet> multiplets, std::vector<Particle> particles, Tag tag, Id id = Id::empty) const {
        INFO(multiplets.size());
        return SaveEntries(BestMatches(multiplets, particles, tag, id));
    }

    int SaveEntries(std::vector<Multiplet> multiplets, Tag tag) const {
        switch (tag) {
            Info0;
        case Tag::signal : return SaveEntries(multiplets, 1);
        case Tag::background : return SaveEntries(multiplets);
        default : return {};
        }
    }

    TClass& Class() const final {
        Info0;
        return *Branch_T::Class();
    }

    void DefineVariables() override {
        Info0;
        ClearObservables();
        AddVariables();
        AddSpectators();
    }

    virtual std::vector<Multiplet> Multiplets(Event const&, PreCuts const&, TMVA::Reader const&) const = 0;

    std::vector<Multiplet> Multiplets(Event const& event, TMVA::Reader const& reader) const {
        Info0;
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    };

private:

    Branch_T const& Branch() const final {
        Info0;
        return branch_;
    }

    void AddVariables() {
        Info0;
        Branch().Variables().AddFilter(Filter());
        for (auto & variable : Branch().Variables().Vector()) AddVariable(variable);
    }

    void AddSpectators() {
        Info0;
        for (auto & spectator : Branch().Spectators().Vector()) AddSpectator(spectator);
    }

    void FillBranch(Multiplet const& multiplet) const {
        Info0;
        branch_.Fill(multiplet);
    }

    /**
    * @brief Branch storing the analysis results
    *
    */
    mutable Branch_T branch_;

};

}

