/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/AnalysisBottom.hh"
#include "boca/standardmodel/BottomTagger.hh"

int main()
{
  boca::standardmodel::AnalysisBottom<boca::standardmodel::BottomTagger> analysis;
  analysis.Run(boca::Output::efficiency);
}
