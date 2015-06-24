# pragma once

# include "Analysis.hh"

namespace analysis{

namespace toppartner {

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * \author Jan Hajer
 *
 */
class Analysis : public analysis::Analysis
{

public:


  Analysis(Tagger &tagger);

  void SetFiles(const Object::Tag tag);

   std::string ProjectName() const {
    return  "TopPartner";
  }

  std::string ProcessName();

  /**
   * @brief Maximal number of Entries to analyse
   *
   */
   int EventNumberMax() const {
    return 1000;
  }

protected:


  virtual  std::string FilePath() const {
    return "~/Projects/TopPartner/Analysis/";
  }

  virtual  std::string NameSpaceName() const {
    return "toppartner";
  }

private:

  int PassPreCut(Event &event);

};

}

}
