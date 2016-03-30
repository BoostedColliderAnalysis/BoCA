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
    void CalculateSignificances(double scaling = 1);
    std::vector<Result> const& Signals() const;
    std::vector<Result> const& Backgrounds() const;
    int BestModelDependentBin() const;
    int BestModelInDependentBin() const;
    int BestAcceptanceBin() const;
    int BestSOverBBin() const;
    double BestModelDependentValue() const;
    double BestModelInDependentValue() const;
    double BestAcceptanceValue() const;
    double BestSOverBValue() const;
    Rectangle<double> const& Range() const;
    Rectangle<double>& Range();
    double XValue(int value) const;
    std::vector<double> const& XValues() const;
    std::vector<double> const& Significances() const;
    std::vector<double> const& Acceptances() const;
    std::vector<double> const& SOverB() const;
    void Efficiencies();
    std::vector<double> const& SelectedEfficiencies() const;
    static double ScalingFactor();
private:
    void CalculateSignificances(double scaling, int step);
    double SignalEvents(int step) const;
    double BackgroundEvents(int step) const;
    double Significance(double signal_events, double background_events) const;
    double Acceptances(double signal_events, double background_events) const;
    double SOverB(double signal_events, double background_events) const;
    Crosssection BackgroundEfficiencyCrosssection(int step) const;
    Crosssection ModelIndependentCrosssection(double signal_efficiency, int step) const;
    Crosssection ModelIndependentCrosssectionSig(double signal_efficiency, int step) const;
    Crosssection ModelIndependentCrosssectionSB(double signal_efficiency, int step) const;
    int Steps() const;
    TMVA::Types::EMVA Mva() const;
    void ExtremeXValues();
    void BestBins();
    Rectangle<double> range_;
    std::vector<Result> signals_;
    std::vector<Result> backgrounds_;
    std::vector<double> significances_;
    std::vector<double> acceptances_;
    std::vector<double> s_over_b_;
    std::vector<double> x_values_;
    int best_model_dependent_bin_ = 0;
    int best_model_independent_bin_ = 0;
    int best_acceptance_bin_ = 0;
    int best_s_over_b_bin_ = 0;
    std::vector<double> selected_efficiencies_;
};

}
