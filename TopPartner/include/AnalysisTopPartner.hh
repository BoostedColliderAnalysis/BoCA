# pragma once

# include "Analysis.hh"

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

  void RunFast();

  void RunNormal();

  void RunFull();

  Analysis(Tagger &tagger);

protected:

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


  virtual  std::string FilePath() const {
    return "~/Projects/TopPartner/Analysis/";
  }

  virtual  std::string NameSpaceName() const {
    return "toppartner";
  }

private:

  int PassPreCut(Event &event);

  void RunTagger(analysis::Tagger::Stage stage);

  void RunFactory();

  void RunReader();

  std::string PathName(const std::string &file_name) const;

  bool Missing(const std::string& name) const;

};

}

}
