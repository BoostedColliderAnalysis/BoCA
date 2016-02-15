/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "TMVA/Reader.h"

#include "ReaderBase.hh"
#include "PreCuts.hh"
#include "Phase.hh"
#include "Options.hh"
#include "Event.hh"

namespace boca
{

/**
 * @brief read results of multivariant analysis
 * wrapper for TMVA::Reader
 *
 */
template<typename Tagger_>
class Reader : public ReaderBase
{

public:

    Reader(Stage stage = Stage::reader) :
        reader_(Options()) {
        stage_ = stage;
        Tagger().Initialize();
        Initialize();
    }

    Reader(Reader const& reader) :
        reader_(Options()),
        stage_(reader.stage_),
        tagger_(reader.tagger_) {
        Initialize();
    }

    Reader(Reader const && reader) :
        reader_(Options()),
        stage_(std::move(reader.stage_)),
        tagger_(std::move(reader.tagger_)) {
        Initialize();
    }

    void Initialize() {
        if (stage_ == Stage::trainer) return;
        std::ofstream cout_file(Tagger().AnalysisName() + "/Reader.txt", std::ios_base::app | std::ios_base::out);
        std::streambuf* cout = std::cout.rdbuf();
        std::cout.rdbuf(cout_file.rdbuf());
        AddObservables();
        BookMva();
        std::cout.rdbuf(cout);
    }

    int Bdt(Event const& event, PreCuts const& pre_cuts) const {
        return Tagger().SaveBdt(event, pre_cuts, TReader());
    }

    template <typename Multiplet_>
    float Bdt(Multiplet_ const& multiplet) const {
        return Tagger().Bdt(multiplet, TReader());
    }

    template <typename Multiplet_>
    Multiplet_ Multiplet(Multiplet_ multiplet, PreCuts const& pre_cuts) const {
        try {
            return Tagger().Multiplet(multiplet, pre_cuts, TReader());
        } catch (std::exception const&) {
            multiplet.SetBdt(-1);
            return multiplet;
        }
    }

    template <typename Input>
    auto Multiplets(Input const& input) const {
        PreCuts pre_cuts;
        return Tagger().Multiplets(input, pre_cuts, TReader());
    }

    template <typename Input>
    auto Jets(Input const& input) const {
        PreCuts pre_cuts;
        return Tagger().Jets(input, pre_cuts, TReader());
    }

    auto Particles(Event const& event) const {
        return Tagger().Particles(event);
    }

    auto Multiplet(Jet& input) const {
        return Tagger().Multiplet(input, TReader());
    }

    template <typename Input>
    auto Multiplet(Input const& input) const {
        return Tagger().Multiplet(input, TReader());
    }

    template <typename Input1, typename Input2>
    auto Multiplet(Input1 const& input_1, Input2 const& input_2) const {
        return Tagger().Multiplet(input_1, input_2, TReader());
    }

    template <typename Input>
    auto SubMultiplet(Input const& input, int number) const {
        return Tagger().SubMultiplet(input, TReader(), number);
    }

    template <typename Input>
    auto SubMultiplet(Input const& input) const {
        return Tagger().SubMultiplet(input, TReader());
    }

    Tagger_ const& Tagger() const {
        return tagger_;
    }

    void NewBranch(exroot::TreeWriter& tree_writer, Stage stage) {
        Tagger().NewBranch(tree_writer, stage);
    }

private:

    std::string Options() const {
        boca::Options options("Color", false);
//         options.Add("V", false);
//         options.Add("Silent");
        return options;
    }

    void AddObservables() {
        std::lock_guard<std::mutex> guard(mutex_);
        for (auto const & variable : Tagger().Variables()) TReader().AddVariable(variable.Expression(), &variable.Value());
        for (auto const & spectator : Tagger().Spectators()) TReader().AddSpectator(spectator.Expression(), &spectator.Value());
    }

    TMVA::IMethod& BookMva() {
        std::lock_guard<std::mutex> guard(mutex_);
        std::cout << Tagger().MethodName() << "  " << Tagger().WeightFileName() << std::endl;
        return *TReader().BookMVA(Tagger().MethodName(), Tagger().WeightFileName());
    }

    TMVA::Reader& TReader() {
        return reader_;
    }

    TMVA::Reader const& TReader() const {
        return reader_;
    }

    Tagger_& Tagger() {
        return tagger_;
    }

    TMVA::Reader reader_;

    Tagger_ tagger_;

    Stage stage_;

};

}

