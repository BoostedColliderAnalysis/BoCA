/**
 * Copyright (C) 2015-2016 Jan Hajer
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
    int BestSOverBBin()const;
    float BestModelDependentValue()const;
    float BestModelInDependentValue()const;
    float BestAcceptanceValue()const;
    float BestSOverBValue()const;
    Rectangle<float> const& Range()const;
    Rectangle<float>& Range();
    float XValue(int value) const;
    std::vector<float> const& XValues()const;
    std::vector<float> const& Significances()const;
    std::vector<float> const& Acceptances()const;
    std::vector<float> const& SOverB() const;
private:
    void CalculateSignificances(int step);
    float SignalEvents(int step) const;
    float BackgroundEvents(int step) const;
    float Significance(float signal_events, float background_events) const;
    float Acceptances(float signal_events, float background_events) const;
    float SOverB(float signal_events, float background_events) const;
    Crosssection BackgroundEfficiencyCrosssection(int step) const;
    Crosssection ModelIndependentCrosssection(double signal_efficiency, int step) const;
    int Steps() const;
    TMVA::Types::EMVA Mva() const;
    void ExtremeXValues();
    void BestBins();
    Rectangle<float> range_;
    std::vector<Result> signals_;
    std::vector<Result> backgrounds_;
    std::vector<float> significances_;
    std::vector<float> acceptances_;
    std::vector<float> s_over_b_;
    std::vector<float> x_values_;
    int best_model_dependent_bin_ = 0;
    int best_model_independent_bin_ = 0;
    int best_acceptance_bin_ = 0;
    int best_s_over_b_bin_ = 0;
};

}
