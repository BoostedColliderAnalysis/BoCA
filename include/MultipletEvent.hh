#pragma once

#include "EventShape.hh"
#include "GlobalObservables.hh"
#include "TwoBody.hh"
#include "JetInfo.hh"

namespace analysis {

/**
 * @brief An event composed of a multiplet an a singlet made up from the remaining jets
 *
 */
template <typename Multiplet_1>
class MultipletEvent : public analysis::TwoBody<Multiplet_1, analysis::Singlet> {

public:

    MultipletEvent(const Multiplet_1& multiplet, const Event& event, Jets& jets) {
        jets_ = jets;
        global_observables_.SetEvent(event);
        Jets unique_jets;
        for (const auto &jet : jets){
          if (!multiplet.Overlap(jet)) 
          {
            unique_jets.emplace_back(jet);
          }
          else
          {  
            signature_jets_.emplace_back(jet);
          }
        }
        global_observables_.SetJets(unique_jets);
        event_shape_.SetJets(signature_jets_);
        analysis::TwoBody<Multiplet_1, analysis::Singlet>::SetMultiplets(multiplet,global_observables_.Singlet());
//         this->SetBdt(Multiplet().Bdt());
    }

    Multiplet_1 Multiplet() const
    {
        return analysis::TwoBody<Multiplet_1, analysis::Singlet>::Multiplet1();
    }

    analysis::Singlet Singlet() const
    {
        return analysis::TwoBody<Multiplet_1, analysis::Singlet>::Multiplet2();
    }

    const analysis::GlobalObservables& GlobalObservables() const
    {
        return global_observables_;
    }
    
    int BottomNumber() const
    {
      analysis::Jets bottoms;
      for (const auto& jet : jets_) if (jet.template user_info<JetInfo>().Bdt() > 0) bottoms.emplace_back(jet);
      return bottoms.size();
    }
    
    int JetNumber() const
    {
      return jets_.size();
    }
    
    int SignatureJetNumber() const
    {
      return signature_jets_.size();
    }
    float BottomBdt(int number) const
    {
      if (number > SignatureJetNumber())
        return 0;
      return signature_jets_.at(number - 1).template user_info<JetInfo>().Bdt();
    }
    
    
    const analysis::EventShape& EventShape() const
    {
      return event_shape_;
    }
    
private:
  
  analysis::EventShape event_shape_;

    analysis::GlobalObservables global_observables_;
    
    Jets jets_;
    
    Jets signature_jets_;

};

}


