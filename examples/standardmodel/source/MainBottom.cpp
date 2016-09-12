/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "standardmodel/analysis/Bottom.hh"
#include "standardmodel/tagger/Bottom.hh"

int main()
{
  standardmodel::analysis::Bottom<standardmodel::tagger::Bottom> analysis;
  analysis.Run(boca::Output::efficiency);
}
