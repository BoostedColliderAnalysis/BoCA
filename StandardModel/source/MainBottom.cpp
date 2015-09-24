/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "AnalysisBottom.hh"
#include "BottomTagger.hh"

int main()
{
    boca::standardmodel::AnalysisBottom<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunFullEfficiency();
    bottom_analysis.RunPlots();
}
