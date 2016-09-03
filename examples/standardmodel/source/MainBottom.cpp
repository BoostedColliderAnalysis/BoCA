/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "standardmodel/AnalysisBottom.hh"
#include "standardmodel/tagger/Bottom.hh"

int main()
{
  standardmodel::AnalysisBottom<standardmodel::tagger::Bottom> analysis;
  analysis.Run(boca::Output::efficiency);
}
