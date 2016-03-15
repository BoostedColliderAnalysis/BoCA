/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "exroot/ExRootAnalysis.hh"

#include "Tagger.hh"
#include "Sort.hh"
#include "PreCuts.hh"
#include "Filter.hh"
#include "Debug.hh"

namespace boca
{

/**
 * @brief Tagger base class using Branch template
 *
 */
template<typename Multiplet_, typename Branch_>
class TaggerTemplate : public Tagger
{

public:

    float Bdt(Multiplet_ const& multiplet, TMVA::Reader const& reader) const {
        FillBranch(multiplet);
        return Tagger::Bdt(reader);
    }

    bool Cut(Multiplet_ const& multiplet, TMVA::Reader const& reader, float effeciency) const {
        FillBranch(multiplet);
        return Tagger::Cut(reader, effeciency);
    }

    std::vector<bool> Cuts(Multiplet_ const& multiplet, TMVA::Reader const& reader) const {
        FillBranch(multiplet);
        std::vector<bool> passed;
        int steps = 50;
        // TODO why is this a 2?
        for (auto const & effeciency : IntegerRange(2, steps)) passed.emplace_back(Tagger::Cut(reader, float(effeciency) / steps));
        return passed;
    }

    Branch_& Branch()override {
        return branch_;
    }

    int SaveBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const override {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    template<typename Input_>
    std::vector<Multiplet_> ReducedMultiplets(const Input_& event, const PreCuts& pre_cuts, const TMVA::Reader& reader, std::size_t max = 4) const {
        return ReduceResult(Multiplets(event, pre_cuts, reader), max);
    }

//     template<typename Input_>
//     std::vector<Multiplet_> ReducedMultiplets(const Input_& event, const TMVA::Reader& reader, std::size_t max = 4) const {
//       PreCuts pre_cuts;
//       return ReduceResult(Multiplets(event, pre_cuts, reader), max);
//     }

    virtual std::vector<Multiplet_> Multiplets(std::vector<Jet> const&, PreCuts const&, TMVA::Reader const&) const {
        std::cout << "Never end up here!" << std::endl;
    }

protected:

    template<typename Multiplet_2_>
    std::vector<Multiplet_2_> ReduceResult(std::vector<Multiplet_2_> multiplets, std::size_t max = 4) const {
        // DEBUG_CHECK(multiplets.size() >= max, multiplets.size());
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        multiplets.erase(multiplets.begin() + std::min(max, multiplets.size()), multiplets.end());
        return multiplets;
    }

    std::vector<Multiplet_> BestRapidity(std::vector<Multiplet_> multiplets, std::size_t number = 1) const {
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMaxDeltaRap(multiplets);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

//     template<typename Multiplet_2_>
//     std::vector<Multiplet_2_> BestMatch(std::vector<Multiplet_2_> const& multiplets, std::vector<Particle> const& particles, Id id = Id::none) const {
//         std::vector<Multiplet_2_> close = CopyIfClose(multiplets, particles);
//         close = SortedByBdt(close);
//         if (id != Id::none) close = SortedByMassTo(close, id);
//         return std::vector<Multiplet_2_>(close.data(), &close.at(std::min(close.size(), particles.size())));
//     }

    template<typename Multiplet_2_, typename Particle_>
    std::vector<Multiplet_2_> BestMatch(std::vector<Multiplet_2_> const& multiplets, std::vector<Particle_> const& particles, Id id = Id::none) const {
        if (Debug()) boca::Debug("multiplets", multiplets.size(), "particles", particles.size());
        if (multiplets.empty()) return multiplets;
        std::vector<Multiplet_2_> best;
        for (auto const & particle : particles) Insert(best, BestMatch(multiplets, particle, id));
        if (Debug()) boca::Debug("best", best.size());
        return best;
    }

    template<typename Multiplet_2_, typename Particle_>
    std::vector<Multiplet_2_> BestMatch(std::vector<Multiplet_2_> const& multiplets, Particle_ const& particle, Id id = Id::none) const {
        if (Debug()) boca::Debug("multiplets", multiplets.size());
        if (multiplets.empty()) return multiplets;
        auto close = CopyIfClose(multiplets, particle);
        close = id == Id::none ? SortedByBdt(close) : SortedByMassTo(close, id);
        if (Debug()) boca::Debug("close", close.size());
        if (close.empty()) return close;
        return {close.front()};
    }

//     template<typename Multiplet_2_>
//     std::vector<Multiplet_2_> BestMatch(std::vector<Multiplet_2_> const& multiplets, std::vector<std::pair<Particle, Particle>> const& particles, Id id = Id::none) const {
//         if (Debug()) boca::Debug("multiplets", multiplets.size(), "particles", particles.size());
//         if (multiplets.empty()) return multiplets;
//         auto close = CopyIfClose(multiplets, particles);
//         if (close.empty()) return close;
//         close = id == Id::none ? SortedByBdt(close) : SortedByMassTo(close, id);
//         if (Debug()) boca::Debug("close", close.size());
//         return close.empty() ? close : std::vector<Multiplet_2_>(close.data(), &close.at(std::min(close.size(), particles.size()) - 1));
//     }

    template<typename Multiplet_2_>
    std::vector<Multiplet_2_> RemoveBestMatch(std::vector<Multiplet_2_> const& multiplets, std::vector<Particle> const& particles) const {
        return RemoveIfClose(multiplets, particles);
    }

    template<typename Multiplet_2_>
    std::vector<Multiplet_2_> RemoveBestMatch(std::vector<Multiplet_2_> const& multiplets, std::vector<std::pair<Particle, Particle>> const& particles) const {
        return RemoveIfClose(multiplets, particles);
    }

    template<typename Multiplet_2_>
    std::vector<Multiplet_2_> BestMatches(std::vector<Multiplet_2_> multiplets, std::vector<Particle> const& particles, Tag tag, Id id = Id::none) const {
        if (Debug()) boca::Debug("multiplets", multiplets.size(), "particles", particles.size());
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        switch (tag) {
        case Tag::signal : return BestMatch(multiplets, particles, id);
        case Tag::background : return RemoveBestMatch(multiplets, particles);
        default : return multiplets;
        }
    }

    template<typename Multiplet_2_>
    std::vector<Multiplet_2_> BestMatches(std::vector<Multiplet_2_> multiplets, std::vector<std::pair<Particle, Particle>> const& particles, Tag tag, Id id = Id::none) const {
        if (Debug()) boca::Debug("multiplets", multiplets.size(), "particles", particles.size());
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        switch (tag) {
        case Tag::signal : return BestMatch(multiplets, particles, id);
        case Tag::background : return RemoveBestMatch(multiplets, particles);
        default : return multiplets;
        }
    }

    int SaveEntries(std::vector<Multiplet_> multiplets, int max = std::numeric_limits<int>::max()) const {
        if (multiplets.size() > 1) multiplets = SortedByBdt(multiplets);
        if (multiplets.empty()) return 0;
        auto sum = std::min(int(multiplets.size()), max);
        for (auto const & counter : IntegerRange(sum)) {
            FillBranch(multiplets.at(counter));
//             std::lock_guard<std::mutex> guard(mutex_);
            static_cast<Branch_&>(*TreeBranch().NewEntry()) = Branch();
        }
        return sum;
    }

    int SaveEntries(std::vector<Multiplet_> multiplets, std::vector<Particle> particles, Tag tag, Id id = Id::none) const {
        if (Debug()) boca::Debug("multiplets", multiplets.size(), "particles", particles.size());
        return SaveEntries(BestMatches(multiplets, particles, tag, id));
    }

    int SaveEntries(std::vector<Multiplet_> multiplets, Tag tag) const {
        switch (tag) {
        case Tag::signal : return SaveEntries(multiplets, 1);
        case Tag::background : return SaveEntries(multiplets);
        default : return {};
        }
    }

    int SaveEntries(std::vector<Multiplet_> multiplets, std::vector<std::pair<Particle, Particle>> particles, Tag tag, Id id = Id::none) const {
        return SaveEntries(BestMatches(multiplets, particles, tag, id));
    }

    TClass& Class() const override {
        return *Branch_::Class();
    }

    void DefineVariables() override {
        ClearObservables();
        AddVariables();
        AddSpectators();
    }

    virtual auto Multiplets(Event const&, PreCuts const&, TMVA::Reader const&) const -> std::vector<Multiplet_> = 0;

    std::vector<Multiplet_> Multiplets(Event const& event, TMVA::Reader const& reader) const {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    };

private:

    Branch_ const& Branch() const override {
        return branch_;
    }

    void AddVariables() {
        Branch().Variables().AddFilter(Filter());
        for (auto & variable : Branch().Variables().Vector()) AddVariable(variable);
    }

    void AddSpectators() {
        for (auto & spectator : Branch().Spectators().Vector()) AddSpectator(spectator);
    }

    void FillBranch(Multiplet_ const& multiplet) const {
        branch_.Fill(multiplet);
    }

    /**
    * @brief Branch storing the analysis results
    *
    */
    mutable Branch_ branch_;

    constexpr bool Debug() const {
        return false;
    }

};

}

