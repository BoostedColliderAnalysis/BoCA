#pragma once

#include "Tagger.hh"
#include "PreCuts.hh"
#include "TMVA/Reader.h"

namespace analysis {

/**
 * @brief read results of multivariant analysis
 * wrapper for TMVA::Reader
 *
 */
template<typename Tagger>
class Reader {

public:

    Reader()
    {
        AddVariable();
        BookMva(TMVA::Types::EMVA::kBDT);
    }

    Reader(Stage stage)
    {
        switch (stage) {
        case Stage::trainer :
            break;
        case Stage::reader :
            AddVariable();
            BookMva(TMVA::Types::EMVA::kBDT);
            break;
        }
    }

    int Bdt(const analysis::Event& event, const analysis::PreCuts& pre_cuts) const
    {
        return tagger_.GetBdt(event, pre_cuts, reader_);
    }

    template <typename Input>
    auto Multiplets(const Input& input) const
    {
        PreCuts pre_cuts;
        return tagger_.Multiplets(input, pre_cuts, reader_);
    }

//     template <typename Input1, typename Input2>
//     auto Multiplets(Input1 &input_1, Input2 &input_2) const {
//         return tagger_.Multiplets(input_1, input_2, reader_);
//     }

    template <typename Input>
    auto Multiplet(const Input& input) const
    {
        return tagger_.Multiplet(input, reader_);
    }

    template <typename Input1, typename Input2>
    auto Multiplet(const Input1& input_1, const Input2& input_2) const
    {
        return tagger_.Multiplet(input_1, input_2, reader_);
    }

    template <typename Input>
    auto SubMultiplet(const Input& input, int number) const
    {
        return tagger_.SubMultiplet(input, reader_, number);
    }

    template <typename Input>
    auto SubMultiplet(const Input& input) const
    {
        return tagger_.SubMultiplet(input, reader_);
    }

    const Tagger& tagger() const
    {
        return tagger_;
    }

    void SetTreeBranch(exroot::TreeWriter& tree_writer,Stage stage)
    {
       tagger().SetTreeBranch(tree_writer, stage);
    }

private:

    Tagger& tagger()
    {
        return tagger_;
    }

    Tagger tagger_;

    const TMVA::Reader& reader() const
    {
        return reader_;
    }

    TMVA::Reader reader_;

    void BookMva(TMVA::Types::EMVA mva)
    {
        //TMVA::IMethod &method = *
      reader_.BookMVA(tagger_.MethodName(mva), tagger_.WeightFileName(mva));
    }

    void AddVariable()
    {
        for (auto& observable : tagger_.Variables()) reader_.AddVariable(observable.expression(), &observable.value());
        for (auto& spectator : tagger_.Spectators()) reader_.AddSpectator(spectator.expression(), &spectator.value());
    }

};

}
