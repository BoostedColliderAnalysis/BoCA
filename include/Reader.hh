#pragma once

#include "Tagger.hh"
#include "PreCuts.hh"

namespace analysis
{

/**
 * @brief Presents result of multivariant analysis
 *
 */
class Reader
{

public:

    void SetTagger(Tagger &tagger);

    int Bdt(const analysis::Event &event, analysis::PreCuts &pre_cuts) const;

    template <typename Tagger, typename Input>
    auto Multiplets(Input &input) const {
        PreCuts pre_cuts;
        return static_cast<Tagger &>(tagger()).Multiplets(input, pre_cuts, reader_);
    }

    template <typename Tagger, typename Input1, typename Input2>
    auto Multiplets(Input1 &input_1, Input2 &input_2) {
        return static_cast<Tagger &>(tagger()).Multiplets(input_1, input_2, reader_);
    }

    template <typename Tagger, typename Input>
    auto Multiplet(Input &input) {
        return static_cast<Tagger &>(tagger()).Multiplet(input, reader_);
    }

    template <typename Tagger, typename Input1, typename Input2>
    auto Multiplet(Input1 &input_1, Input2 &input_2) {
        return static_cast<Tagger &>(tagger()).Multiplet(input_1, input_2, reader_);
    }

    template <typename Tagger, typename Input>
    auto SubMultiplet(Input &input, const int number) {
        return static_cast<Tagger &>(tagger()).SubMultiplet(input, reader_, number);
    }

    template <typename Tagger, typename Input>
    auto SubMultiplet(Input &input) {
        return static_cast<Tagger &>(tagger()).SubMultiplet(input, reader_);
    }

private:

    const TMVA::Reader &reader() const;

    Tagger &tagger() const;

    Tagger *tagger_;

    TMVA::Reader reader_;

    void BookMva();

    void AddVariable();

};

}
