# pragma once

# include "HTag.hh"

namespace hanalysis {
class Singlet : public HTag
{

public:

    Singlet(const fastjet::PseudoJet &singlet);

    inline fastjet::PseudoJet singlet() const {
        return singlet_;
    }

    float Pt(){
      return singlet().pt();
    }

    float Mass(){
      return singlet().m();
    }

    float Eta(){
      return singlet().rap();
    }

    float Phi(){
      return singlet().phi_std();
    }

protected:

    virtual inline std::string ClassName() const {
        return "Singlet";
    }

private:

    fastjet::PseudoJet singlet_;

};
}
