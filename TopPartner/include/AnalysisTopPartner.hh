#pragma once

#include "Analysis.hh"

namespace analysis{

namespace toppartner {

/**
 *
 * @brief Top partner analysis
 *
 * \author Jan Hajer
 *
 */
class Analysis : public analysis::Analysis
{

public:

  Analysis(Tagger &tagger);

protected:

  void SetFiles(const Tag tag);

   std::string ProjectName() const;

  std::string ProcessName();

  /**
   * @brief Maximal number of Entries to analyse
   *
   */
   int EventNumberMax() const;

  virtual  std::string FilePath() const;


private:

  int PreCut() const;

  int PassPreCut(const Event &event);

};

}

}
