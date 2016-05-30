/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/standardmodel/AnalysisBottom.hh"
#include "boca/standardmodel/tagger/Bottom.hh"

int main()
{
  boca::standardmodel::AnalysisBottom<boca::standardmodel::tagger::Bottom> analysis;
  analysis.Run(boca::Output::efficiency);
}
