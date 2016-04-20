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
    Results(const std::vector< boca::Result >& signals, const std::vector< boca::Result >& backgrounds);
    void CalculateSignificances();
    std::vector<Result> const& Signals() const;
    std::vector<Result> const& Backgrounds() const;
    Rectangle<double> const& Range() const;
    Rectangle<double>& Range();
    double XValue(int value) const;
    std::vector<double> const& XValues() const;
    void Efficiencies();
    std::vector<double> const& SelectedEfficiencies() const;
    static double ScalingFactor();
private:
    void CalculateSignificances(Result& signal,Significance significance, int step);
    double SignalEvents(int step) const;
    double BackgroundEvents(int step) const;
    Crosssection BackgroundEfficiencyCrosssection(int step) const;
    Crosssection MI(Significance significance, double signal_efficiency, int step) const;
    Crosssection MIConstrained(Significance significance, double signal_efficiency, int step) const;
    Crosssection MISum(double signal_efficiency, int step) const;
    Crosssection MIExperimental(double signal_efficiency, int step) const;
    Crosssection MIBackground(double signal_efficiency, int step) const;
    Crosssection MIPoisson(double signal_efficiency, int step) const;
    int Steps() const;
    TMVA::Types::EMVA Mva() const;
    void ExtremeXValues();
    void BestBins(boca::Result& signal, boca::Significance significance);
    Rectangle<double> range_;
    std::vector<Result> signals_;
    std::vector<Result> backgrounds_;
    std::vector<double> x_values_;
    std::vector<double> selected_efficiencies_;
};

}
