/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "physics/Rectangle.hh"
#include "plotting/Result.hh"

namespace boca
{

class Results
{
public:
    Results(std::vector<Result> signals, std::vector<Result> backgrounds);
    void CalculateSignificances();
    std::vector<Result> const& Signals()const;
    std::vector<Result> const& Backgrounds()const;
    int BestModelDependentBin()const;
    int BestModelInDependentBin()const;
    int BestAcceptanceBin()const;
    float BestModelDependentValue()const;
    float BestModelInDependentValue()const;
    float BestAcceptanceValue()const;
    Rectangle<float> const& Bounds()const;
    Rectangle<float>& Bounds();
    float XValue(int value) const;
    std::vector<float> const& XValues()const;
    std::vector<float> const& Significances()const;
    std::vector<float> const& Acceptances()const;
    std::vector<Crosssection> const& ModelIndependentCrosssection()const;
    std::vector<Crosssection>& ModelIndependentCrosssection();
private:
    int Steps() const;
    TMVA::Types::EMVA Mva() const;
    void ExtremeXValues();
    void BestBin();
    Rectangle<float> bounds_;
    std::vector<Result> signals_;
    std::vector<Result> backgrounds_;
    std::vector<float> significances_;
    std::vector<float> acceptances_;
    std::vector<Crosssection> crosssections_;
    std::vector<float> x_values_;
    int best_model_dependent_bin_ = 0;
    int best_model_independent_bin_ = 0;
    int best_acceptance_bin_ = 0;
};

}
