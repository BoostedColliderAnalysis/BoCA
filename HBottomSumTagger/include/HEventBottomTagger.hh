#pragma once

#include "BottomTagger.hh"
#include "Reader.hh"
#include "Branches.hh"

namespace hbottomsumtagger
{

// class EventBottomMultiplet : public analysis::
// {
// public:
//
// //     float Bdt() const {
// //       float bdt =0;
// //       for (int i = 1; i < 6; ++i) bdt += TotalBottomBdt(i);
// //       return bdt;
// //     }
//
//
//      float TotalBottomBdt(const unsigned Number) const {
//         if (jets_.size() < Number) return 0;
//         return jets_.at(Number - 1).user_info<analysis::JetInfo>().Bdt();
//     }
//
//      float TotalBottomBdt(const unsigned Number1, const unsigned Number2) const {
//         return TotalBottomBdt(Number1) + TotalBottomBdt(Number2);
//     }
//
//      float TotalBottomBdt(const unsigned Number1, const unsigned Number2, const unsigned Number3) const {
//         return TotalBottomBdt(Number1) + TotalBottomBdt(Number2) + TotalBottomBdt(Number3);
//     }
//
//      float TotalBottomBdt(const unsigned Number1, const unsigned Number2, const unsigned Number3, const unsigned Number4) const {
//         return TotalBottomBdt(Number1) + TotalBottomBdt(Number2) + TotalBottomBdt(Number3) + TotalBottomBdt(Number4);
//     }
//
//     void SetJets(const analysis::Jets &NewJets) {
//         jets_ = NewJets;
//         float bdt = 0;
//         for (int i = 1; i < 6; ++i) bdt += TotalBottomBdt(i);
//         SetBdt(bdt);
//     }
//
// private:
//
//     analysis::Jets jets_;
//
// };


/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventBottomTagger : public analysis::BranchTagger<analysis::EventBottomTaggerBranch>
{

public:

    /**
    * @brief Constructor
    *
    */
    EventBottomTagger();

    bool TruthLevelCheck(const analysis::Jets &NewJets, analysis::Event &event, const analysis::Tag Tag);

    int Train(analysis::Event &event, const analysis::Tag tag);

    int Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual  std::string NameSpaceName() const {
      return "hbottomsumtagger";
    }

    virtual  std::string ClassName() const {
        return "EventBottomTagger";
    }

private:

    void DefineVariables();

    analysis::BottomTagger bottom_tagger_;

    analysis::Reader bottom_reader_;

};

}
