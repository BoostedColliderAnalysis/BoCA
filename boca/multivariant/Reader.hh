/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TMVA/Reader.h"

#include "boca/generic/Options.hh"
// #include "boca/io/TreeWriter.hh"
// #include "boca/fastjet/Sort.hh"
#include "boca/multivariant/Phase.hh"
#include "boca/identification/PreCuts.hh"
#include "boca/event/Event.hh"

namespace boca
{

class TreeWriter;

/**
 * @brief read results of multivariant analysis
 * wrapper for TMVA::Reader
 *
 */
template<typename Tagger_>
class Reader
{

public:

    Reader(Stage stage = Stage::reader) :
        stage_(stage),
        reader_(Options()) {
//         Initialize();
    }

    Reader(Reader const& reader) :
        stage_(reader.stage_),
        reader_(Options()),
        tagger_(reader.tagger_) {
//         Initialize();
    }

    Reader(Reader const && reader) :
        stage_(std::move(reader.stage_)),
        reader_(Options()),
        tagger_(std::move(reader.tagger_)) {
//         Initialize();
    }

    void Initialize() {
        initialized_ = true;
        if (Debug()) std::cout << "Reader: " << Tagger().Name() << '\n';
        Tagger().Initialize();
        if (stage_ == Stage::trainer) return;
        std::ofstream cout_file(Tagger().AnalysisName() + "/Reader.txt", std::ios_base::app | std::ios_base::out);
        auto cout = std::cout.rdbuf();
        std::cout.rdbuf(cout_file.rdbuf());
        AddObservables();
        BookMva();
        std::cout.rdbuf(cout);
    }

    int Bdt(Event const& event, PreCuts const& pre_cuts) {
        return Tagger().SaveBdt(event, pre_cuts, TReader());
    }

    template <typename Multiplet_>
    double Bdt(Multiplet_ const& multiplet) {
        if (Debug()) std::cout << "Reader: " << Tagger().Name() << " reading bdt" << '\n';
        return Tagger().Bdt(multiplet, TReader());
    }

    template <typename Multiplet_>
    Multiplet_ Multiplet(Multiplet_ multiplet, PreCuts const& pre_cuts) const {
        try {
            return Tagger().Multiplet(multiplet, pre_cuts, TReader());
        } catch (std::exception const&) {
            multiplet.SetBdt(Tagger().MvaRange().Min());
            return multiplet;
        }
    }

    template <typename Input_>
    auto Multiplets(Input_ const& input, std::size_t number = 4) {
        PreCuts pre_cuts;
        return Tagger().ReducedMultiplets(input, pre_cuts, TReader(), number);
    }

    template <typename Input_>
    auto Jets(Input_ const& input) {
        PreCuts pre_cuts;
        return Tagger().Jets(input, pre_cuts, TReader());
    }

    auto Particles(Event const& event) const {
        return Tagger().Particles(event);
    }

    auto Multiplet(Jet& input) {
        return Tagger().Multiplet(input, TReader());
    }

    template <typename Input_>
    auto Multiplet(Input_ const& input) {
        return Tagger().Multiplet(input, TReader());
    }

    template <typename Input_1_, typename Input_2_>
    auto Multiplet(Input_1_ const& input_1, Input_2_ const& input_2) {
        return Tagger().Multiplet(input_1, input_2, TReader());
    }

    template <typename Input_>
    auto SubMultiplet(Input_ const& input, int number) {
        return Tagger().SubMultiplet(input, TReader(), number);
    }

    template <typename Input_>
    auto SubMultiplet(Input_ const& input) {
        return Tagger().SubMultiplet(input, TReader());
    }

    Tagger_ const& Tagger() const {
        if (!initialized_) const_cast<Reader*>(this)->Initialize();
        return tagger_;
    }

    void NewBranch(TreeWriter& tree_writer, Stage stage) {
        Tagger().NewBranch(tree_writer, stage);
    }

    template<typename Multiplet_>
    auto Transform(Event const& event) {
        auto multiplets = std::vector<Multiplet_>{};
        for (auto const & multiplet : Multiplets(event)) {
            auto new_multiplet = Multiplet_{};
            new_multiplet.Enforce(multiplet);
            multiplets.emplace_back(new_multiplet);
        }
        return multiplets;
    }

    Tagger_& Tagger() {
        if (!initialized_) Initialize();
        return tagger_;
    }

protected:

    TMVA::Reader const& TReader() const {
        if (!initialized_) const_cast<Reader*>(this)->Initialize();
        return reader_;
    }

private:

    std::string Options() const {
        boca::Options options("Color", false);
//         options.Add("V", false);
//         options.Add("Silent");
        return options;
    }

    void AddObservables() {
        for (auto const & variable : Tagger().Variables()) TReader().AddVariable(variable.Expression(), &variable.Value());
        for (auto const & spectator : Tagger().Spectators()) TReader().AddSpectator(spectator.Expression(), &spectator.Value());
    }

    TMVA::IMethod& BookMva() {
        std::cout << Tagger().MethodName() << "  " << Tagger().WeightFileName() << '\n';
        return *TReader().BookMVA(Tagger().MethodName(), Tagger().WeightFileName());
    }

    TMVA::Reader& TReader() {
        if (!initialized_) Initialize();
        return reader_;
    }

    constexpr bool Debug() const {
        return false;
    }

    Stage stage_;

    TMVA::Reader reader_;

    Tagger_ tagger_;

    bool initialized_ = false;

};

}



