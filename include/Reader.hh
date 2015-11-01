/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once
#include <mutex>

#include "TMVA/Reader.h"

#include "PreCuts.hh"
#include "Tagger.hh"
#include "Options.hh"

namespace boca
{

/**
 * @brief read results of multivariant analysis
 * wrapper for TMVA::Reader
 *
 */
template<typename TaggerTemplate>
class Reader
{

public:

    Reader() { //: reader_(Options())
        reader_ = new TMVA::Reader(Options());
        Initialize();
    }

    Reader(Stage stage) { //: reader_(Options())
        stage_ = stage;
        reader_ = new TMVA::Reader(Options());
        switch (stage) {
        case Stage::trainer :
            Tagger().Initialize();
            break;
        case Stage::reader :
            Initialize();
            break;
        }
    }

    ~Reader() {
        delete reader_;
    }

    Reader(const Reader& that) {
        stage_ = that.stage_;
        reader_ = new TMVA::Reader(Options());
        switch (stage_) {
        case Stage::trainer :
            Tagger().Initialize();
            break;
        case Stage::reader :
            Initialize();
            break;
        }
        tagger_ = that.tagger_;
    }

    Reader& operator=(Reader const& that) {
      stage_ = that.stage_;
        reader_ = new TMVA::Reader(Options());
        switch (stage_) {
        case Stage::trainer :
            Tagger().Initialize();
            break;
        case Stage::reader :
            Initialize();
            break;
        }
        tagger_ = that.tagger_;
        return *this;
    }

    void Initialize() {
        std::lock_guard<std::mutex> guard(mutex);
        Tagger().Initialize();
//         std::ofstream cout_file(Tagger().AnalysisName() + "/Reader.txt", std::ios_base::app | std::ios_base::out);
//         std::streambuf* cout = std::cout.rdbuf();
//         std::cout.rdbuf(cout_file.rdbuf());
        AddObservables();
        BookMva(TMVA::Types::EMVA::kBDT);
//         std::cout.rdbuf(cout);
    }

    int Bdt(Event const& event, PreCuts const& pre_cuts) const {
        return Tagger().SaveBdt(event, pre_cuts, reader());
    }

    template <typename Multiplet>
    float Bdt(Multiplet const& multiplet) const {
        return Tagger().Bdt(multiplet, reader());
    }

    template <typename Plet>
    Plet Multiplet(Plet multiplet, PreCuts const& pre_cuts) const {
        try {
            return Tagger().Multiplet(multiplet, pre_cuts, reader());
        } catch (std::exception const&) {
            multiplet.SetBdt(-1);
            return multiplet;
        }
    }

    template <typename Input>
    auto Multiplets(Input const& input) const {
        PreCuts pre_cuts;
        return Tagger().Multiplets(input, pre_cuts, reader());
    }

    template <typename Input>
    auto Jets(Input const& input) const {
        PreCuts pre_cuts;
        return Tagger().Jets(input, pre_cuts, reader());
    }

//     template <typename Input1, typename Input2>
//     auto Multiplets(Input1 &input_1, Input2 &input_2) const {
//         return Tagger().Multiplets(input_1, input_2, reader());
//     }

    template <typename Input>
    auto Multiplet(Input const& input) const {
        return Tagger().Multiplet(input, reader());
    }

    template <typename Input1, typename Input2>
    auto Multiplet(Input1 const& input_1, Input2 const& input_2) const {
        return Tagger().Multiplet(input_1, input_2, reader());
    }

    template <typename Input>
    auto SubMultiplet(Input const& input, int number) const {
        return Tagger().SubMultiplet(input, reader(), number);
    }

    template <typename Input>
    auto SubMultiplet(Input const& input) const {
        return Tagger().SubMultiplet(input, reader());
    }

    TaggerTemplate const& Tagger() const {
        return tagger_;
    }

    void SetTreeBranch(exroot::TreeWriter& tree_writer, Stage stage) {
        Tagger().SetTreeBranch(tree_writer, stage);
    }

    TMVA::Reader const& reader() const {
        return *reader_;
    }

private:

    std::string Options() const {
        boca::Options options;
//         options.Add("V", false);
        options.Add("Color", false);
//         options.Add("Silent");
        return options;
    }

    void AddObservables() {
        for (auto const & observable : Tagger().Variables()) reader().AddVariable(observable.expression(), &observable.value());
        for (auto const & spectator : Tagger().Spectators()) reader().AddSpectator(spectator.expression(), &spectator.value());
    }

    TMVA::IMethod& BookMva(TMVA::Types::EMVA mva) {
        return *reader().BookMVA(Tagger().MethodName(mva), Tagger().WeightFileName(mva));
    }

    TMVA::Reader& reader() {
        return *reader_;
    }

    TaggerTemplate& Tagger() {
        return tagger_;
    }

    TMVA::Reader* reader_;

    TaggerTemplate tagger_;

    Stage stage_;

    std::mutex mutex;

};

}
