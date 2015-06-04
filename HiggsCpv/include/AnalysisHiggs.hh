# pragma once

// # include "SignatureTagger.hh"
# include "Analysis.hh"
// # include "BranchesHiggsCpv.hh"

// # include "SubStructure.hh"
// # include "Doublet.hh"
// # include "Reader.hh"
// # include "Factory.hh"
// # include "TopLeptonicTagger.hh"

namespace higgscpv {
//
// class HHiggsCpv
// {
//
// public:
//
//     analysis::Doublet higgs_;
//
//     analysis::Doublet top_;
//
//     analysis::Doublet anti_top_;
//
//     HHiggsCpv(const analysis::Doublet &higgs, const analysis::Doublet &top, const analysis::Doublet &anti_top) {
//         higgs_ = higgs;
//         top_ = top;
//         anti_top_ = anti_top;
//     };
//
//     float Bdt() const {
//         return (higgs_.Bdt() * top_.Bdt() * anti_top_.Bdt());
//     }
//
//     float GetTopDeltaRap() const {
//         return (top_.Singlet1().rap() - anti_top_.Singlet1().rap());
//     }
//
//     float GetTopDeltaPhi() const {
//         return (top_.Singlet1().delta_phi_to(anti_top_.Singlet1()));
//     }
//
//     float GetTopDeltaR() const {
//         return (top_.Singlet1().delta_R(anti_top_.Singlet1()));
//     }
//
// };


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


  Analysis(analysis::Tagger &tagger);

  void SetFiles(const analysis::Object::Tag tag);

  inline std::string ProjectName() const {
    return  "HiggsCpv-" + std::to_string(PreCut()) + "GeV-";
  }

  std::string ProcessName();

protected:


  virtual inline std::string FilePath() const {
    return "~/Projects/HiggsCpv/";
  }

  virtual inline std::string NameSpaceName() const {
    return "higgscpv";
  }

private:

  int PassPreCut(analysis::Event &event);

  /**
   * @brief Main Analysis function
   *
   */
  int RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const Tag tag);

};

}
