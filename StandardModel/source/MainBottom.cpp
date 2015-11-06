/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "AnalysisBottom.hh"
#include "BottomTagger.hh"

int main()
{
    boca::standardmodel::AnalysisBottom<boca::standardmodel::BottomTagger> analysis;
    analysis.RunFullEfficiency();
    analysis.RunPlots();
}
